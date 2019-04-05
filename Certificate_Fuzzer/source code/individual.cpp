#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <openssl/pem.h>
#include <openssl/conf.h>
#include <openssl/x509v3.h>
#ifndef OPENSSL_NO_ENGINE
#include <openssl/engine.h>
#endif

    char *version;
    char *serial;
    char *iso;
    char *icn;
    char *nc;
    char *so;
    char *scn;
    char *vpnb;
    char *vpna;
    char *op;



static void callback(int p, int n, void *arg)
	{
	char c='B';

	if (p == 0) c='.';
	if (p == 1) c='+';
	if (p == 2) c='*';
	if (p == 3) c='\n';
	fputc(c,stderr);
	}


/* Add extension using V3 code: we can set the config file as NULL
 * because we wont reference any other sections.
 */

int add_ext(X509 *cert, int nid, char *value)
	{
	X509_EXTENSION *ex;
	X509V3_CTX ctx;
	/* This sets the 'context' of the extensions. */
	/* No configuration database */
	X509V3_set_ctx_nodb(&ctx);
	/* Issuer and subject certs: both the target since it is self signed,
	 * no request and no CRL
	 */
	X509V3_set_ctx(&ctx, cert, cert, NULL, NULL, 0);
	ex = X509V3_EXT_conf_nid(NULL, &ctx, nid, value);
	if (!ex)
		return 0;

	X509_add_ext(cert,ex,-1);
	X509_EXTENSION_free(ex);
	return 1;
	}
	



int mkcert(X509 **x509p, EVP_PKEY **pkeyp, int bits, int serial, int days)
{
    X509 *x;
	EVP_PKEY *pk;
	RSA *rsa;
	X509_NAME *name=NULL;
	
	if ((pkeyp == NULL) || (*pkeyp == NULL))
		{
		if ((pk=EVP_PKEY_new()) == NULL)
			{
			abort(); 
			return(0);
			}
		}
	else
		pk= *pkeyp;

	if ((x509p == NULL) || (*x509p == NULL))
		{
		if ((x=X509_new()) == NULL)
			goto err;
		}
	else
		x= *x509p;

	rsa=RSA_generate_key(bits,RSA_F4,callback,NULL);
	if (!EVP_PKEY_assign_RSA(pk,rsa))
		{
		abort();
		goto err;
		}
	rsa=NULL;

	X509_set_version(x,1);
	ASN1_INTEGER_set(X509_get_serialNumber(x),2);
	X509_gmtime_adj(X509_get_notBefore(x),(int)vpnb);
	X509_gmtime_adj(X509_get_notAfter(x),(int)vpna);
	X509_set_pubkey(x,pk);

	name=X509_get_subject_name(x);


	X509_NAME_add_entry_by_txt(name,"C",
				MBSTRING_ASC, so, -1, -1, 0);
	X509_NAME_add_entry_by_txt(name,"CN",
				MBSTRING_ASC,scn, -1, -1, 0);

	X509_set_issuer_name(x,name);

	/* Add various extensions: standard extensions */
	add_ext(x, NID_basic_constraints, "critical,CA:TRUE");
	add_ext(x, NID_key_usage, "critical,keyCertSign,cRLSign");

	add_ext(x, NID_subject_key_identifier, "hash");

	/* Some Netscape specific extensions */
	add_ext(x, NID_netscape_cert_type, "sslCA");

	add_ext(x, NID_netscape_comment, nc);


#ifdef CUSTOM_EXT
	/* Maybe even add our own extension based on existing */
	{
		int nid;
		nid = OBJ_create("1.2.3.4", "MyAlias", "My Test Alias Extension");
		X509V3_EXT_add_alias(nid, NID_netscape_comment);
		add_ext(x, nid, "example comment alias");
	}
#endif
	
	if (!X509_sign(x,pk,EVP_sha1()))
		goto err;

	*x509p=x;
	*pkeyp=pk;

	return(1);
err:
	return(0);



}



int main(int argc, char **argv)
	{
	BIO *bio_err;
	X509 *x509=NULL;
	EVP_PKEY *pkey=NULL;

	CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ON);

	bio_err=BIO_new_fp(stderr, BIO_NOCLOSE);



    int option = 0;
 int choice,ret;
    int ratio,n;
    char cert_filestr[100] = "";
    char *dest = NULL;

    while ((option = getopt(argc, argv,"v:s:i:c:n:z:y:x:w:o:")) != -1) {
        switch (option) {
             case 'v' : 
             version=optarg;
             break;
             case 's' : 
             serial=optarg;
                 break;
             case 'i' : 
             iso=optarg;
                 break;
              case 'c':
              icn=optarg;
              break;
              
               case 'n':
              nc=optarg;
              break;

              case 'z':
              so=optarg;
              break;

               case 'y':
              scn=optarg;
              break;

               case 'x':
              vpnb=optarg;
              break;

               case 'w':
              vpna=optarg;
              break;

               case 'o':
              op=optarg;
              break;
             default: 
                 exit(EXIT_FAILURE);
        }
    }



	mkcert(&x509,&pkey,512,0,365);
    
    char out1[100],out2[100];
    snprintf(out1,sizeof(out1),"%s/createdpem.pem",op);
    snprintf(out2,sizeof(out2),"%s/createdkey.key",op);
    FILE *f= fopen(out1, "w");
    FILE *g= fopen(out2,"w");

	// RSA_print_fp(stdout,pkey->pkey.rsa,0);
	// X509_print_fp(stdout,x509);

	PEM_write_PrivateKey(g,pkey,NULL,NULL,0,NULL, NULL);
	PEM_write_X509(f,x509);

	X509_free(x509);
	EVP_PKEY_free(pkey);



	#ifndef OPENSSL_NO_ENGINE
	ENGINE_cleanup();
#endif
	CRYPTO_cleanup_all_ex_data();

	CRYPTO_mem_leaks(bio_err);
	BIO_free(bio_err);
	return(0);
	}

