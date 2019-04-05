	#include <stdio.h>
    #include <iostream>
	#include <openssl/x509.h>
	#include <openssl/x509v3.h>
    #include <openssl/pem.h>
    #include <memory>
    #include <string>
    #include <openssl/bio.h>
    #include <openssl/err.h>
    #include <openssl/x509.h>

    using namespace std;

    using X509_ptr = unique_ptr<X509, decltype(&::X509_free)>;
    using BIO_MEM_ptr = unique_ptr<BIO, decltype(&::BIO_free)>;

    int main()

    {
    const char *path="test.pem";	

	FILE *fp = fopen(path, "r");
	if (!fp) {
		fprintf(stderr, "unable to open: %s\n", path);
		return EXIT_FAILURE;
	}
	
	X509 *cert = PEM_read_X509(fp, NULL, NULL, NULL);
	if (!cert) {
		fprintf(stderr, "unable to parse certificate in: %s\n", path);
		fclose(fp);
		return EXIT_FAILURE;
	}


	int rc = 0;
    unsigned long err = 0;


    X509_ptr x509(cert, ::X509_free);
    BIO_MEM_ptr bio(BIO_new(BIO_s_mem()), ::BIO_free);

    rc = PEM_write_bio_X509(bio.get(), x509.get());
    err = ERR_get_error();

    if (rc != 1)
    {
        cerr << "PEM_write_bio_X509 failed, error " << err << ", ";
        cerr << hex << "0x" << err;
        exit(1);
    }

    BUF_MEM *mem = NULL;
    BIO_get_mem_ptr(bio.get(), &mem);
    err = ERR_get_error();

    if (!mem || !mem->data || !mem->length)
    {
        cerr << "BIO_get_mem_ptr failed, error " << err << ", ";
        cerr << hex << "0x" << err;
        exit(2);
    }

    string pem1(mem->data, mem->length);
    cout << pem1<< endl;
    const char * pem_c_str = pem1.c_str();
	

    //Display content of pem file

    BIO *bio_mem = BIO_new(BIO_s_mem());
    BIO_puts(bio_mem, pem_c_str);
    X509 * x509_1 = PEM_read_bio_X509(bio_mem, NULL, NULL, NULL);
    X509 * x = x509_1;
    BIO *bio_out = BIO_new_fp(stdout, BIO_NOCLOSE);
    long l = X509_get_version(x509_1);
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
    X509_free(x509_1);
	X509_free(cert);
	fclose(fp);

    }



 
