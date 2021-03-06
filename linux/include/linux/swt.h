/*
 * include/linux/swt.h - Support for Openstack Swift through the nbd module
 *
 * Copyright 2012, José Ramón Muñoz Pekkarinen <koalinux@gmail.com>
 * Released under the General Public License (GPL).
 *
 */

#ifndef _SWT_H
#define _SWT_H

#include <linux/types.h>

enum swt_ops {
	SWT_AUTH,
	SWT_CONTAINER_LIST,
	SWT_CONTAINER_CREATE,
	SWT_CONTAINER_DELETE,
	SWT_OBJECT_LIST,
	SWT_OBJECT_RETRIEVE,
	SWT_OBJECT_CREATE,
	SWT_OBJECT_DELETE,
};

char * swt_ops_format[] = {
	"GET /v1.0 HTTP/1.1\nHost: %s\nX-Auth-User: %s\nX-Auth-Key: %s\n",
	"GET /%s?format=xml HTTP/1.1\nHost: %s\nX-Auth-Token: %s\n",
	"PUT /%s/%s HTTP/1.1\nHost: %s\nX-Auth-Token: %s\n",
	"DELETE /%s/%s HTTP/1.1\nHost: %s\nX-Auth-Token: %s\n",
	"GET /%s/%s HTTP/1.1\nHost: %s\nX-Auth-Token: %s\n",
	"GET /%s/%s/%s HTTP/1.1\nHost: %s\nX-Auth-Token: %s\n",
	"PUT /%s/%s/%s HTTP/1.1\nHost: %s\nX-Auth-Token: %s\nContent-Length: %i\n%s",
	"DELETE /%s/%s/%s HTTP/1.1\nHost: %s\nX-Auth-Token: %s\n"
};

char * swt_ans_format[] = {
	"HTTP/1.1 204 No Content\n%*s\nX-Storage-Url: %s\nX-Storage-Token: %s\n%*s",
	"%*s<name>%s</name>\n%*s\n<bytes>%d</bytes>\n",
	"HTTP/1.1 201 Created\n",
	"HTTP/1.1 204 No Content\n",
	"%*s<object>\n%*s<name>%s</name>\n%*s<bytes>%d</bytes>\n%*s</object>\n",
	"HTTP/1.1 200 Ok%*s\nContent-Length: %d\n%s",
	"HTTP/1.1 201 Created\n%*s\nContent-Length: %d\n%*s",
	"HTTP/1.1 204 No Content\n%*s"
};

struct swt_op {
	int op;
	const char * container;
	const char * object;
	struct request * req;
};

struct object
{
	char * name;
	int size;
	struct object * next;
};

struct container
{
	char * name;
	int size;
	struct container * next;
	struct object * first;
};

struct swt_reply {
	int op;
	int size;
	struct list_head unprocessed;
};

#endif
