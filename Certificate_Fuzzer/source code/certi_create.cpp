#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <random>
#include <openssl/x509.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <string> 
#include <cstring>
#include <getopt.h>
#include <openssl/pem.h>
#include <openssl/conf.h>
#include <openssl/x509v3.h>
#ifndef OPENSSL_NO_ENGINE
#include <openssl/engine.h>
#endif
using namespace std;

int mkcert(X509 **, EVP_PKEY **, int , int, int,char *,int);
int add_ext(X509 *cert, int nid, char *value);


int fuzzer_call(double number,int i)
{

 char fuzzer_command[256];
 snprintf(fuzzer_command, sizeof(fuzzer_command), 
          "zzuf -r %lf cat /tmp/serial.srl > serial%d.srl", 
          number, i);
// cout<<fuzzer_command<<endl;
 int zzuf_err = system(fuzzer_command);
 // if (zzuf_err) { fprintf(stderr, "failed to %s\n", fuzzer_command);}	
 if (zzuf_err) { fprintf(stderr, "failed to run fuzzer command");}	
 system(fuzzer_command);

}

double randomize(double a,double b)
{
 random_device rd;
 default_random_engine generator(rd()); 
 uniform_real_distribution<double> distribution(a,b);
 double number = distribution(generator); 
 return number;
}



int main(int argc, char **argv)
	{
	BIO *bio_err;
	X509 *x509=NULL;
	EVP_PKEY *pkey=NULL;

	CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ON);

	bio_err=BIO_new_fp(stderr, BIO_NOCLOSE);

    FILE *_privKeyFile;

    

      OpenSSL_add_all_algorithms();
  ERR_load_BIO_strings();
  ERR_load_crypto_strings();


 int option = 0;
 int choice,ret;
    int ratio,n;
    char cert_filestr[100] = "";
    char dest[100]="";
int field=1;

// c - certificate  r-ratio n-number of files  b-base  k-key  o-output dir -f field to be fuzzed

    while ((option = getopt(argc, argv,"c:r:n:k:o:f:")) != -1) {
        switch (option) {
             case 'c' : 
             //Base certificate
             // char var2[16];
             // char *var;
              snprintf(cert_filestr, sizeof(cert_filestr), "%s", optarg);
             // std::strcpy(cert_filestr,optarg);
             printf("%s",cert_filestr);
             break;
             case 'r' : 
             //Fuzz ratio -- 1/2/3/4 i.e. Low/medium/high/extreme
             ratio=atoi(optarg);
                 break;
             case 'n' : 
             //No of certificates
             n = atoi(optarg); 
                 break;
             case 'k':
             //Base key
             _privKeyFile = fopen(optarg, "rt");
             pkey = PEM_read_PrivateKey(_privKeyFile, NULL, NULL, NULL);           

             break;
             case 'o':
             //O/p dir for files
             snprintf(dest, sizeof(dest), "%s", optarg);
             break;
             case 'f':
             field=atoi(optarg);   
             //field to be fuzzed
             break;    
             default: 
                 exit(EXIT_FAILURE);
        }
    }

//     if (cert_filestr=="") {
//         exit(EXIT_FAILURE);
//     }


   BIO *bio_mem = BIO_new(BIO_s_file());
   
 ret = BIO_read_filename(bio_mem, cert_filestr);
// ret = BIO_read_filename(bio_mem, "success.pem");
    X509 * x5091 = PEM_read_bio_X509(bio_mem, NULL, NULL, NULL);
    X509 * x = x5091;
    printf("%s",X509_get_issuer_name(x));


choice=ratio;
switch(choice)
{
case 1 :
for(int i=1;i<=n;i++)
{


 x509=NULL;	
 fuzzer_call(randomize(0.21,0.50),i);
 
 char fname[100];
 char *fuzzed_val;
 snprintf(fname,sizeof(fname),"serial%d.srl",i);
 
 FILE *fuzzed_val_file=fopen(fname,"r");
    size_t fuzzindex = 0;
    int c;

    fuzzed_val = malloc(1000);

    while ((c = fgetc(fuzzed_val_file)) != EOF)
    {
        fuzzed_val[fuzzindex++] = (char) c;
    }

    // don't forget to terminate with the null character
    fuzzed_val[fuzzindex] = '\0'; 

 mkcert(&x509,&pkey,512,0,365,fuzzed_val,field);
	// RSA_print_fp(stdout,pkey->pkey.rsa,0);
	// X509_print_fp(stdout,x509);

 char buffer[500];
 //snprintf(buffer, sizeof(char) * 500, "/home/bharath/citrix/testing/ss%i.pem", i);
 snprintf(buffer, sizeof(char) * 500,"%s/ss%i.pem",dest,i);
  printf("\n%s",buffer);
   // printf("\nBuffer :%s",buffer);
 FILE *f= fopen(buffer, "w");
 PEM_write_X509(f,x509);
 fclose(f);
    
 char buffer_1[500];
// snprintf(buffer_1, sizeof(char) * 500, "/home/bharath/citrix/testing/ss%i.key", i);
  snprintf(buffer_1, sizeof(char) * 500,"%s/ss%i.key",dest,i);
  printf("\n%s",buffer_1);
 FILE *g= fopen(buffer_1, "w");

	//FILE *f=fopen("/home/bharath/citrix/ss.pem","w");
	//FILE *g=fopen("/home/bharath/citrix/ss.key","w");
 PEM_write_PrivateKey(g,pkey,NULL,NULL,0,NULL, NULL);
 fclose(g);

}
break;

case 2 :
for(int i=1;i<=n;i++)
{


 x509=NULL;	
 fuzzer_call(randomize(0.50,0.77),i);
 
 char fname[100];
 char *fuzzed_val;
 snprintf(fname,sizeof(fname),"serial%d.srl",i);
 
 FILE *fuzzed_val_file=fopen(fname,"r");
    size_t fuzzindex = 0;
    int c;

    fuzzed_val = malloc(1000);

    while ((c = fgetc(fuzzed_val_file)) != EOF)
    {
        fuzzed_val[fuzzindex++] = (char) c;
    }

    // don't forget to terminate with the null character
    fuzzed_val[fuzzindex] = '\0'; 

 mkcert(&x509,&pkey,512,0,365,fuzzed_val,field);
	// RSA_print_fp(stdout,pkey->pkey.rsa,0);
	// X509_print_fp(stdout,x509);

 char buffer[500];
 //snprintf(buffer, sizeof(char) * 500, "/home/bharath/citrix/testing/ss%i.pem", i);
 snprintf(buffer, sizeof(char) * 500,"%s/ss%i.pem",dest,i);
  printf("\n%s",buffer);
   // printf("\nBuffer :%s",buffer);
 FILE *f= fopen(buffer, "w");
 PEM_write_X509(f,x509);
 fclose(f);
    
 char buffer_1[500];
// snprintf(buffer_1, sizeof(char) * 500, "/home/bharath/citrix/testing/ss%i.key", i);
  snprintf(buffer_1, sizeof(char) * 500,"%s/ss%i.key",dest,i);
  printf("\n%s",buffer_1);
 FILE *g= fopen(buffer_1, "w");

	//FILE *f=fopen("/home/bharath/citrix/ss.pem","w");
	//FILE *g=fopen("/home/bharath/citrix/ss.key","w");
 PEM_write_PrivateKey(g,pkey,NULL,NULL,0,NULL, NULL);
 fclose(g);

}
break;

case 3 :
for(int i=1;i<=n;i++)
{


 x509=NULL;	
 fuzzer_call(randomize(0.77,0.90),i);
 
 char fname[100];
 char *fuzzed_val;
 snprintf(fname,sizeof(fname),"serial%d.srl",i);
 
 FILE *fuzzed_val_file=fopen(fname,"r");
    size_t fuzzindex = 0;
    int c;

    fuzzed_val = malloc(1000);

    while ((c = fgetc(fuzzed_val_file)) != EOF)
    {
        fuzzed_val[fuzzindex++] = (char) c;
    }

    // don't forget to terminate with the null character
    fuzzed_val[fuzzindex] = '\0'; 

 mkcert(&x509,&pkey,512,0,365,fuzzed_val,field);
	// RSA_print_fp(stdout,pkey->pkey.rsa,0);
	// X509_print_fp(stdout,x509);

 char buffer[500];
 //snprintf(buffer, sizeof(char) * 500, "/home/bharath/citrix/testing/ss%i.pem", i);
 snprintf(buffer, sizeof(char) * 500,"%s/ss%i.pem",dest,i);
  printf("\n%s",buffer);
   // printf("\nBuffer :%s",buffer);
 FILE *f= fopen(buffer, "w");
 PEM_write_X509(f,x509);
 fclose(f);
    
 char buffer_1[500];
// snprintf(buffer_1, sizeof(char) * 500, "/home/bharath/citrix/testing/ss%i.key", i);
  snprintf(buffer_1, sizeof(char) * 500,"%s/ss%i.key",dest,i);
  printf("\n%s",buffer_1);
 FILE *g= fopen(buffer_1, "w");

	//FILE *f=fopen("/home/bharath/citrix/ss.pem","w");
	//FILE *g=fopen("/home/bharath/citrix/ss.key","w");
 PEM_write_PrivateKey(g,pkey,NULL,NULL,0,NULL, NULL);
 fclose(g);

}
break;

case 4 :
for(int i=1;i<=n;i++)
{


 x509=NULL;	
 fuzzer_call(randomize(0.91,1.00),i);
 
 char fname[100];
 char *fuzzed_val;
 snprintf(fname,sizeof(fname),"serial%d.srl",i);
 
 FILE *fuzzed_val_file=fopen(fname,"r");
    size_t fuzzindex = 0;
    int c;

    fuzzed_val = malloc(1000);

    while ((c = fgetc(fuzzed_val_file)) != EOF)
    {
        fuzzed_val[fuzzindex++] = (char) c;
    }

    // don't forget to terminate with the null character
    fuzzed_val[fuzzindex] = '\0'; 

 mkcert(&x509,&pkey,512,0,365,fuzzed_val,field);
	// RSA_print_fp(stdout,pkey->pkey.rsa,0);
	// X509_print_fp(stdout,x509);

 char buffer[500];
 //snprintf(buffer, sizeof(char) * 500, "/home/bharath/citrix/testing/ss%i.pem", i);
 snprintf(buffer, sizeof(char) * 500,"%s/ss%i.pem",dest,i);
  printf("\n%s",buffer);
   // printf("\nBuffer :%s",buffer);
 FILE *f= fopen(buffer, "w");
 PEM_write_X509(f,x509);
 fclose(f);
    
 char buffer_1[500];
// snprintf(buffer_1, sizeof(char) * 500, "/home/bharath/citrix/testing/ss%i.key", i);
  snprintf(buffer_1, sizeof(char) * 500,"%s/ss%i.key",dest,i);
  printf("\n%s",buffer_1);
 FILE *g= fopen(buffer_1, "w");

	//FILE *f=fopen("/home/bharath/citrix/ss.pem","w");
	//FILE *g=fopen("/home/bharath/citrix/ss.key","w");
 PEM_write_PrivateKey(g,pkey,NULL,NULL,0,NULL, NULL);
 fclose(g);

}
break;

default : printf("\nInvalid option entered !!!"); 
break;

}

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

static void callback(int p, int n, void *arg)
	{
	char c='B';

	if (p == 0) c='.';
	if (p == 1) c='+';
	if (p == 2) c='*';
	if (p == 3) c='\n';
	fputc(c,stderr);
	}

int mkcert(X509 **x509p, EVP_PKEY **pkeyp, int bits, int serial, int days,char * fuzzed_val,int field)  
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


// _rsa = EVP_PKEY_get1_RSA(_privKey);
// 	rsa=RSA_generate_key(bits,RSA_F4,callback,NULL);
// 	if (!EVP_PKEY_assign_RSA(pk,rsa))
// 		{
// 		abort();
// 		goto err;
// 		}
// 	rsa=NULL;
    if(field==1||field==6)
	X509_set_version(x,fuzzed_val);
    if(field==2||field==6) 
	ASN1_INTEGER_set(X509_get_serialNumber(x),fuzzed_val);
	X509_gmtime_adj(X509_get_notBefore(x),fuzzed_val);
	X509_gmtime_adj(X509_get_notAfter(x),fuzzed_val);
	X509_set_pubkey(x,pk);

	name=X509_get_subject_name(x);
printf("%s\n",name);
	X509_NAME_add_entry_by_txt(name,"",
				MBSTRING_ASC, fuzzed_val, -1, -1, 0);
	if(field==3||field==6)
	X509_NAME_add_entry_by_txt(name, "O",  MBSTRING_ASC,
                           (unsigned char *)fuzzed_val, -1, -1, 0);
	if(field==4||field==6)
	X509_NAME_add_entry_by_txt(name,"CN",
				MBSTRING_ASC, fuzzed_val, -1, -1, 0);
	X509_set_issuer_name(x,name);

	add_ext(x, NID_basic_constraints, fuzzed_val);
	add_ext(x, NID_key_usage, fuzzed_val);

	add_ext(x, NID_subject_key_identifier, fuzzed_val);

	add_ext(x, NID_netscape_cert_type, fuzzed_val);
    if(field==5||field==6)
	add_ext(x, NID_netscape_comment, fuzzed_val);


#ifdef CUSTOM_EXT
	{
		int nid;
		nid = OBJ_create("1.2.3.4", "MyAlias", "My Test Alias Extension");
		X509V3_EXT_add_alias(nid, NID_netscape_comment);
		add_ext(x, nid, "example comment alias");
	}
#endif
	
	if (!X509_sign(x,pk,EVP_md5()))
		goto err;

	*x509p=x;
	*pkeyp=pk;
	return(1);
err:
	return(0);
	}

int add_ext(X509 *cert, int nid, char *value)
	{
	X509_EXTENSION *ex;
	X509V3_CTX ctx;

	X509V3_set_ctx_nodb(&ctx);

	X509V3_set_ctx(&ctx, cert, cert, NULL, NULL, 0);
	ex = X509V3_EXT_conf_nid(NULL, &ctx, nid, value);
	if (!ex)
		return 0;

	X509_add_ext(cert,ex,-1);
	X509_EXTENSION_free(ex);
	return 1;
	}
