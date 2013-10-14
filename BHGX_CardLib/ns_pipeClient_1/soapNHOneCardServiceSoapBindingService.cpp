/* soapNHOneCardServiceSoapBindingService.cpp
   Generated by gSOAP 2.8.15 from cardWSDL.h

Copyright(C) 2000-2013, Robert van Engelen, Genivia Inc. All Rights Reserved.
The generated code is released under ONE of the following licenses:
GPL or Genivia's license for commercial use.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
*/

#include "soapNHOneCardServiceSoapBindingService.h"

NHOneCardServiceSoapBindingService::NHOneCardServiceSoapBindingService()
{	NHOneCardServiceSoapBindingService_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

NHOneCardServiceSoapBindingService::NHOneCardServiceSoapBindingService(const struct soap &_soap) : soap(_soap)
{ }

NHOneCardServiceSoapBindingService::NHOneCardServiceSoapBindingService(soap_mode iomode)
{	NHOneCardServiceSoapBindingService_init(iomode, iomode);
}

NHOneCardServiceSoapBindingService::NHOneCardServiceSoapBindingService(soap_mode imode, soap_mode omode)
{	NHOneCardServiceSoapBindingService_init(imode, omode);
}

NHOneCardServiceSoapBindingService::~NHOneCardServiceSoapBindingService()
{ }

void NHOneCardServiceSoapBindingService::NHOneCardServiceSoapBindingService_init(soap_mode imode, soap_mode omode)
{	soap_imode(this, imode);
	soap_omode(this, omode);
	static const struct Namespace namespaces[] =
{
	{"SOAP-ENV", "http://www.w3.org/2003/05/soap-envelope", "http://schemas.xmlsoap.org/soap/envelope/", NULL},
	{"SOAP-ENC", "http://www.w3.org/2003/05/soap-encoding", "http://schemas.xmlsoap.org/soap/encoding/", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns1", "http://tempurl.org", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
	soap_set_namespaces(this, namespaces);
};

void NHOneCardServiceSoapBindingService::destroy()
{	soap_destroy(this);
	soap_end(this);
}

void NHOneCardServiceSoapBindingService::reset()
{	destroy();
	soap_done(this);
	soap_init(this);
	NHOneCardServiceSoapBindingService_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

#ifndef WITH_PURE_VIRTUAL
NHOneCardServiceSoapBindingService *NHOneCardServiceSoapBindingService::copy()
{	NHOneCardServiceSoapBindingService *dup = SOAP_NEW_COPY(NHOneCardServiceSoapBindingService(*(struct soap*)this));
	return dup;
}
#endif

int NHOneCardServiceSoapBindingService::soap_close_socket()
{	return soap_closesock(this);
}

int NHOneCardServiceSoapBindingService::soap_force_close_socket()
{	return soap_force_closesock(this);
}

int NHOneCardServiceSoapBindingService::soap_senderfault(const char *string, const char *detailXML)
{	return ::soap_sender_fault(this, string, detailXML);
}

int NHOneCardServiceSoapBindingService::soap_senderfault(const char *subcodeQName, const char *string, const char *detailXML)
{	return ::soap_sender_fault_subcode(this, subcodeQName, string, detailXML);
}

int NHOneCardServiceSoapBindingService::soap_receiverfault(const char *string, const char *detailXML)
{	return ::soap_receiver_fault(this, string, detailXML);
}

int NHOneCardServiceSoapBindingService::soap_receiverfault(const char *subcodeQName, const char *string, const char *detailXML)
{	return ::soap_receiver_fault_subcode(this, subcodeQName, string, detailXML);
}

void NHOneCardServiceSoapBindingService::soap_print_fault(FILE *fd)
{	::soap_print_fault(this, fd);
}

#ifndef WITH_LEAN
#ifndef WITH_COMPAT
void NHOneCardServiceSoapBindingService::soap_stream_fault(std::ostream& os)
{	::soap_stream_fault(this, os);
}
#endif

char *NHOneCardServiceSoapBindingService::soap_sprint_fault(char *buf, size_t len)
{	return ::soap_sprint_fault(this, buf, len);
}
#endif

void NHOneCardServiceSoapBindingService::soap_noheader()
{	this->header = NULL;
}

const SOAP_ENV__Header *NHOneCardServiceSoapBindingService::soap_header()
{	return this->header;
}

int NHOneCardServiceSoapBindingService::run(int port)
{	if (soap_valid_socket(this->master) || soap_valid_socket(bind(NULL, port, 100)))
	{	for (;;)
		{	if (!soap_valid_socket(accept()) || serve())
				return this->error;
			soap_destroy(this);
			soap_end(this);
		}
	}
	else
		return this->error;
	return SOAP_OK;
}

SOAP_SOCKET NHOneCardServiceSoapBindingService::bind(const char *host, int port, int backlog)
{	return soap_bind(this, host, port, backlog);
}

SOAP_SOCKET NHOneCardServiceSoapBindingService::accept()
{	return soap_accept(this);
}

#if defined(WITH_OPENSSL) || defined(WITH_GNUTLS)
int NHOneCardServiceSoapBindingService::ssl_accept()
{	return soap_ssl_accept(this);
}
#endif

int NHOneCardServiceSoapBindingService::serve()
{
#ifndef WITH_FASTCGI
	unsigned int k = this->max_keep_alive;
#endif
	do
	{

#ifndef WITH_FASTCGI
		if (this->max_keep_alive > 0 && !--k)
			this->keep_alive = 0;
#endif

		if (soap_begin_serve(this))
		{	if (this->error >= SOAP_STOP)
				continue;
			return this->error;
		}
		if (dispatch() || (this->fserveloop && this->fserveloop(this)))
		{
#ifdef WITH_FASTCGI
			soap_send_fault(this);
#else
			return soap_send_fault(this);
#endif
		}

#ifdef WITH_FASTCGI
		soap_destroy(this);
		soap_end(this);
	} while (1);
#else
	} while (this->keep_alive);
#endif
	return SOAP_OK;
}

static int serve___ns1__nh_USCOREpipe(NHOneCardServiceSoapBindingService*);

int NHOneCardServiceSoapBindingService::dispatch()
{	soap_peek_element(this);
	if (!soap_match_tag(this, this->tag, "ns1:nh_pipe"))
		return serve___ns1__nh_USCOREpipe(this);
	return this->error = SOAP_NO_METHOD;
}

static int serve___ns1__nh_USCOREpipe(NHOneCardServiceSoapBindingService *soap)
{	struct __ns1__nh_USCOREpipe soap_tmp___ns1__nh_USCOREpipe;
	ns1__nh_USCOREpipeResponse ns1__nh_USCOREpipeResponse_;
	ns1__nh_USCOREpipeResponse_.soap_default(soap);
	soap_default___ns1__nh_USCOREpipe(soap, &soap_tmp___ns1__nh_USCOREpipe);
	soap->encodingStyle = NULL;
	if (!soap_get___ns1__nh_USCOREpipe(soap, &soap_tmp___ns1__nh_USCOREpipe, "-ns1:nh_pipe", NULL))
		return soap->error;
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap->error;
	soap->error = soap->nh_USCOREpipe(soap_tmp___ns1__nh_USCOREpipe.ns1__nh_USCOREpipe_, &ns1__nh_USCOREpipeResponse_);
	if (soap->error)
		return soap->error;
	soap_serializeheader(soap);
	ns1__nh_USCOREpipeResponse_.soap_serialize(soap);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || ns1__nh_USCOREpipeResponse_.soap_put(soap, "ns1:nh_pipeResponse", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	};
	if (soap_end_count(soap)
	 || soap_response(soap, SOAP_OK)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || ns1__nh_USCOREpipeResponse_.soap_put(soap, "ns1:nh_pipeResponse", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap->error;
	return soap_closesock(soap);
}
/* End of server object code */