#include <stdio.h>
#include <iostream>
#include <random>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <string> 
int main()
{
int choice,ret;

  OpenSSL_add_all_algorithms();
  ERR_load_BIO_strings();
  ERR_load_crypto_strings();

char cert_filestr[100] = "";
printf("\nEnter initial PEM file to be loaded :");
scanf("%s",&cert_filestr);
    FILE *fp = fopen(cert_filestr, "r");
    if (!fp) {
        fprintf(stderr, "unable to open: %s\n", cert_filestr);
        return EXIT_FAILURE;
    }
 
BIO *bio_mem = BIO_new(BIO_s_file());
    
 ret = BIO_read_filename(bio_mem, cert_filestr);

    X509 * x509 = PEM_read_bio_X509(bio_mem, NULL, NULL, NULL);
    X509 * x = x509;
 
    BIO *bio_out = BIO_new_fp(stdout, BIO_NOCLOSE);

    long l = X509_get_version(x509);
    BIO_printf(bio_out, "Version: %ld\n", l+1);
 
    int i=0;
    ASN1_INTEGER *bs = X509_get_serialNumber(x);
    BIO_printf(bio_out,"Serial: ");
    for(i=0; i<bs->length; i++)
    {
        BIO_printf(bio_out,"%02x",bs->data[i] );
    }
    BIO_printf(bio_out,"\n");
 
    X509_signature_print(bio_out, x->sig_alg, NULL);
 
    BIO_printf(bio_out,"Issuer: ");
    X509_NAME_print(bio_out,X509_get_issuer_name(x),0);
    BIO_printf(bio_out,"\n");
 
    BIO_printf(bio_out,"Valid From: ");
    ASN1_TIME_print(bio_out,X509_get_notBefore(x));
    BIO_printf(bio_out,"\n");
 
    BIO_printf(bio_out,"Valid Until: ");
    ASN1_TIME_print(bio_out,X509_get_notAfter(x));
    BIO_printf(bio_out,"\n");
 
    BIO_printf(bio_out,"Subject: ");
    X509_NAME_print(bio_out,X509_get_subject_name(x),0);
    BIO_printf(bio_out,"\n");
 
    EVP_PKEY *pkey=X509_get_pubkey(x);
    EVP_PKEY_print_public(bio_out, pkey, 0, NULL);
    EVP_PKEY_free(pkey);
 
    X509_CINF *ci=x->cert_info;
    X509V3_extensions_print(bio_out, "X509v3 extensions", ci->extensions, X509_FLAG_COMPAT, 0);
 
    X509_signature_print(bio_out, x->sig_alg, x->signature);
 
 
    BIO_free(bio_out);
    BIO_free(bio_mem);
    X509_free(x509);
}