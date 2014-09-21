/*
 * Python object definition of the libfwsi item
 *
 * Copyright (c) 2010-2014, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H )
#include <stdlib.h>
#endif

#include "pyfwsi_error.h"
#include "pyfwsi_extension_block.h"
#include "pyfwsi_extension_blocks.h"
#include "pyfwsi_file_entry_extension.h"
#include "pyfwsi_item.h"
#include "pyfwsi_item_list.h"
#include "pyfwsi_libcerror.h"
#include "pyfwsi_libclocale.h"
#include "pyfwsi_libcstring.h"
#include "pyfwsi_libfwsi.h"
#include "pyfwsi_python.h"
#include "pyfwsi_unused.h"

PyMethodDef pyfwsi_item_object_methods[] = {

	/* Functions to access the item data */

	{ "get_class_type",
	  (PyCFunction) pyfwsi_item_get_class_type,
	  METH_NOARGS,
	  "get_class_type() -> Integer\n"
	  "\n"
	  "Returns the class type." },

	{ "get_data_size",
	  (PyCFunction) pyfwsi_item_get_data_size,
	  METH_NOARGS,
	  "get_data_size() -> Integer\n"
	  "\n"
	  "Returns the size of the item data." },

#ifdef TODO
	{ "get_data",
	  (PyCFunction) pyfwsi_item_get_data,
	  METH_NOARGS,
	  "get_data() -> String or None\n"
	  "\n"
	  "Returns the item data." },
#endif

	/* Functions to access the extension blocks */

	{ "get_number_of_extension_blocks",
	  (PyCFunction) pyfwsi_item_get_number_of_extension_blocks,
	  METH_NOARGS,
	  "get_number_of_extension_blocks() -> Integer\n"
	  "\n"
	  "Retrieves the number of extension blocks." },

	{ "get_extension_block",
	  (PyCFunction) pyfwsi_item_get_extension_block,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_extension_block(extension_block_index) -> Object\n"
	  "\n"
	  "Retrieves a specific extension block." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyfwsi_item_object_get_set_definitions[] = {

	{ "class_type",
	  (getter) pyfwsi_item_get_class_type,
	  (setter) 0,
	  "The class type.",
	  NULL },

	{ "data_size",
	  (getter) pyfwsi_item_get_data_size,
	  (setter) 0,
	  "The size of the item data.",
	  NULL },

#ifdef TODO
	{ "data",
	  (getter) pyfwsi_item_get_data,
	  (setter) 0,
	  "The item data.",
	  NULL },
#endif

	{ "number_of_extension_blocks",
	  (getter) pyfwsi_item_get_number_of_extension_blocks,
	  (setter) 0,
	  "The number of extension blocks.",
	  NULL },

	{ "extension_blocks",
	  (getter) pyfwsi_item_get_extension_blocks,
	  (setter) 0,
	  "The extension blocks",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyfwsi_item_type_object = {
	PyObject_HEAD_INIT( NULL )

	/* ob_size */
	0,
	/* tp_name */
	"pyfwsi.item",
	/* tp_basicsize */
	sizeof( pyfwsi_item_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyfwsi_item_free,
	/* tp_print */
	0,
	/* tp_getattr */
	0,
	/* tp_setattr */
	0,
	/* tp_compare */
	0,
	/* tp_repr */
	0,
	/* tp_as_number */
	0,
	/* tp_as_sequence */
	0,
	/* tp_as_mapping */
	0,
	/* tp_hash */
	0,
	/* tp_call */
	0,
	/* tp_str */
	0,
	/* tp_getattro */
	0,
	/* tp_setattro */
	0,
	/* tp_as_buffer */
	0,
	/* tp_flags */
	Py_TPFLAGS_DEFAULT,
	/* tp_doc */
	"pyfwsi item object (wraps libfwsi_item_t)",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	0,
	/* tp_iternext */
	0,
	/* tp_methods */
	pyfwsi_item_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyfwsi_item_object_get_set_definitions,
	/* tp_base */
	0,
	/* tp_dict */
	0,
	/* tp_descr_get */
	0,
	/* tp_descr_set */
	0,
	/* tp_dictoffset */
	0,
	/* tp_init */
	(initproc) pyfwsi_item_init,
	/* tp_alloc */
	0,
	/* tp_new */
	0,
	/* tp_free */
	0,
	/* tp_is_gc */
	0,
	/* tp_bases */
	NULL,
	/* tp_mro */
	NULL,
	/* tp_cache */
	NULL,
	/* tp_subclasses */
	NULL,
	/* tp_weaklist */
	NULL,
	/* tp_del */
	0
};

/* Creates a new pyfwsi item object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwsi_item_new(
           PyTypeObject *type_object,
           libfwsi_item_t *item,
           pyfwsi_item_list_t *item_list_object )
{
	pyfwsi_item_t *pyfwsi_item = NULL;
	static char *function      = "pyfwsi_item_new";

	if( item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	pyfwsi_item = PyObject_New(
	               struct pyfwsi_item,
	               type_object );

	if( pyfwsi_item == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize item.",
		 function );

		goto on_error;
	}
	if( pyfwsi_item_init(
	     pyfwsi_item ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize item.",
		 function );

		goto on_error;
	}
	pyfwsi_item->item             = item;
	pyfwsi_item->item_list_object = item_list_object;

	Py_IncRef(
	 (PyObject *) pyfwsi_item->item_list_object );

	return( (PyObject *) pyfwsi_item );

on_error:
	if( pyfwsi_item != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyfwsi_item );
	}
	return( NULL );
}

/* Intializes an item object
 * Returns 0 if successful or -1 on error
 */
int pyfwsi_item_init(
     pyfwsi_item_t *pyfwsi_item )
{
	static char *function = "pyfwsi_item_init";

	if( pyfwsi_item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	pyfwsi_item->item             = NULL;
	pyfwsi_item->item_list_object = NULL;

	return( 0 );
}

/* Frees an item object
 */
void pyfwsi_item_free(
      pyfwsi_item_t *pyfwsi_item )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwsi_item_free";
	int result               = 0;

	if( pyfwsi_item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item.",
		 function );

		return;
	}
	if( pyfwsi_item->ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item - missing ob_type.",
		 function );

		return;
	}
	if( pyfwsi_item->ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item - invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	if( pyfwsi_item->item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item - missing libfwsi item.",
		 function );

		return;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwsi_item_free(
	          &( pyfwsi_item->item ),
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwsi_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to free item.",
		 function );

		libcerror_error_free(
		 &error );
	}
	if( pyfwsi_item->item_list_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyfwsi_item->item_list_object );
	}
	pyfwsi_item->ob_type->tp_free(
	 (PyObject*) pyfwsi_item );
}

/* Retrieves the class type
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwsi_item_get_class_type(
           pyfwsi_item_t *pyfwsi_item,
           PyObject *arguments PYFWSI_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwsi_item_get_class_type";
	uint8_t class_type       = 0;
	int result               = 0;

	PYFWSI_UNREFERENCED_PARAMETER( arguments )

	if( pyfwsi_item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwsi_item_get_class_type(
	          pyfwsi_item->item,
	          &class_type,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwsi_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve class type.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	return( PyLong_FromUnsignedLong(
	         (unsigned long) class_type ) );
}

/* Retrieves the data size
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwsi_item_get_data_size(
           pyfwsi_item_t *pyfwsi_item,
           PyObject *arguments PYFWSI_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyfwsi_item_get_data_size";
	size_t data_size         = 0;
	int result               = 0;

	PYFWSI_UNREFERENCED_PARAMETER( arguments )

	if( pyfwsi_item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwsi_item_get_data_size(
	          pyfwsi_item->item,
	          &data_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwsi_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve data size.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	return( PyLong_FromUnsignedLong(
	         (unsigned long) data_size ) );
}

#ifdef TODO
/* Retrieves the data
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwsi_item_get_data(
           pyfwsi_item_t *pyfwsi_item,
           PyObject *arguments PYFWSI_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	uint8_t *data            = NULL;
	static char *function    = "pyfwsi_item_get_data";
	size_t data_size         = 0;
	int result               = 0;

	PYFWSI_UNREFERENCED_PARAMETER( arguments )

	if( pyfwsi_item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwsi_item_get_data_size(
	          pyfwsi_item->item,
	          &data_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyfwsi_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve data size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( data_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	data = (uint8_t *) PyMem_Malloc(
	                    sizeof( uint8_t ) * data_size );

	if( data == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to create data.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwsi_item_get_data(
		  pyfwsi_item->item,
		  data,
		  data_size,
		  &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwsi_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve data.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	string_object = PyString_FromStringAndSize(
			 (char *) data,
			 (Py_ssize_t) data_size );

	PyMem_Free(
	 data );

	return( string_object );

on_error:
	if( data != NULL )
	{
		PyMem_Free(
		 data );
	}
	return( NULL );
}
#endif

/* Retrieves the number of extension blocks
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwsi_item_get_number_of_extension_blocks(
           pyfwsi_item_t *pyfwsi_item,
           PyObject *arguments PYFWSI_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error       = NULL;
	static char *function          = "pyfwsi_item_get_number_of_extension_blocks";
	int number_of_extension_blocks = 0;
	int result                     = 0;

	PYFWSI_UNREFERENCED_PARAMETER( arguments )

	if( pyfwsi_item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwsi_item_get_number_of_extension_blocks(
	          pyfwsi_item->item,
	          &number_of_extension_blocks,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwsi_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of extension blocks.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	return( PyInt_FromLong(
	         (long) number_of_extension_blocks ) );
}

/* Retrieves a specific extension block by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwsi_item_get_extension_block_by_index(
           pyfwsi_item_t *pyfwsi_item,
           int extension_block_index )
{
	libcerror_error_t *error                   = NULL;
	libfwsi_extension_block_t *extension_block = NULL;
	PyObject *extension_block_object           = NULL;
	PyTypeObject *type_object                  = NULL;
	static char *function                      = "pyfwsi_item_get_extension_block_by_index";
	uint32_t signature                         = 0;
	int result                                 = 0;

	if( pyfwsi_item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwsi_item_get_extension_block(
	          pyfwsi_item->item,
	          extension_block_index,
	          &extension_block,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwsi_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve extension block: %d.",
		 function,
		 extension_block_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwsi_extension_block_get_signature(
	          extension_block,
	          &signature,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwsi_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve extension block: %d signature.",
		 function,
		 extension_block_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	switch( signature )
	{
		case 0xbeef0004UL:
			type_object = &pyfwsi_file_entry_extension_type_object;
			break;

		default:
			type_object = &pyfwsi_extension_block_type_object;
			break;
	}
	extension_block_object = pyfwsi_extension_block_new(
	                          type_object,
	                          extension_block,
	                          pyfwsi_item );

	if( extension_block_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create extension block object.",
		 function );

		goto on_error;
	}
	return( extension_block_object );

on_error:
	if( extension_block != NULL )
	{
		libfwsi_extension_block_free(
		 &extension_block,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific extension block
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwsi_item_get_extension_block(
           pyfwsi_item_t *pyfwsi_item,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *extension_block_object = NULL;
	static char *keyword_list[]      = { "extension_block_index", NULL };
	int extension_block_index        = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &extension_block_index ) == 0 )
	{
		return( NULL );
	}
	extension_block_object = pyfwsi_item_get_extension_block_by_index(
	                          pyfwsi_item,
	                          extension_block_index );

	return( extension_block_object );
}

/* Retrieves an extension blocks sequence and iterator object for the extension blocks
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwsi_item_get_extension_blocks(
           pyfwsi_item_t *pyfwsi_item,
           PyObject *arguments PYFWSI_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error          = NULL;
	PyObject *extension_blocks_object = NULL;
	static char *function             = "pyfwsi_item_get_extension_blocks";
	int number_of_extension_blocks    = 0;
	int result                        = 0;

	PYFWSI_UNREFERENCED_PARAMETER( arguments )

	if( pyfwsi_item == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid item.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfwsi_item_get_number_of_extension_blocks(
	          pyfwsi_item->item,
	          &number_of_extension_blocks,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfwsi_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of extension blocks.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	extension_blocks_object = pyfwsi_extension_blocks_new(
	                           pyfwsi_item,
	                           &pyfwsi_item_get_extension_block_by_index,
	                           number_of_extension_blocks );

	if( extension_blocks_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create extension blocks object.",
		 function );

		return( NULL );
	}
	return( extension_blocks_object );
}
