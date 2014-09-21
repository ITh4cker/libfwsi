/*
 * Python bindings module for libfwsi (pyfwsi)
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

#include "pyfwsi.h"
#include "pyfwsi_error.h"
#include "pyfwsi_extension_block.h"
#include "pyfwsi_extension_blocks.h"
#include "pyfwsi_file_entry.h"
#include "pyfwsi_file_entry_extension.h"
#include "pyfwsi_item.h"
#include "pyfwsi_item_list.h"
#include "pyfwsi_items.h"
#include "pyfwsi_libcerror.h"
#include "pyfwsi_libcstring.h"
#include "pyfwsi_libfwsi.h"
#include "pyfwsi_network_location.h"
#include "pyfwsi_python.h"
#include "pyfwsi_root_folder.h"
#include "pyfwsi_unused.h"
#include "pyfwsi_volume.h"

/* The pyfwsi module methods
 */
PyMethodDef pyfwsi_module_methods[] = {
	{ "get_version",
	  (PyCFunction) pyfwsi_get_version,
	  METH_NOARGS,
	  "get_version() -> String\n"
	  "\n"
	  "Retrieves the version." },

	/* Sentinel */
	{ NULL,
	  NULL,
	  0,
	  NULL}
};

/* Retrieves the pyfwsi/libfwsi version
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfwsi_get_version(
           PyObject *self PYFWSI_ATTRIBUTE_UNUSED,
           PyObject *arguments PYFWSI_ATTRIBUTE_UNUSED )
{
	const char *errors           = NULL;
	const char *version_string   = NULL;
	size_t version_string_length = 0;

	PYFWSI_UNREFERENCED_PARAMETER( self )
	PYFWSI_UNREFERENCED_PARAMETER( arguments )

	Py_BEGIN_ALLOW_THREADS

	version_string = libfwsi_get_version();

	Py_END_ALLOW_THREADS

	version_string_length = libcstring_narrow_string_length(
	                         version_string );

	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	return( PyUnicode_DecodeUTF8(
	         version_string,
	         (Py_ssize_t) version_string_length,
	         errors ) );
}

/* Declarations for DLL import/export
 */
#ifndef PyMODINIT_FUNC
#define PyMODINIT_FUNC void
#endif

/* Initializes the pyfwsi module
 */
PyMODINIT_FUNC initpyfwsi(
                void )
{
	PyObject *module                               = NULL;
	PyTypeObject *extension_block_type_object      = NULL;
	PyTypeObject *extension_blocks_type_object     = NULL;
	PyTypeObject *file_entry_type_object           = NULL;
	PyTypeObject *file_entry_extension_type_object = NULL;
	PyTypeObject *item_type_object                 = NULL;
	PyTypeObject *item_list_type_object            = NULL;
	PyTypeObject *items_type_object                = NULL;
	PyTypeObject *network_location_type_object     = NULL;
	PyTypeObject *root_folder_type_object          = NULL;
	PyTypeObject *volume_type_object               = NULL;
	PyGILState_STATE gil_state                     = 0;

	/* Create the module
	 * This function must be called before grabbing the GIL
	 * otherwise the module will segfault on a version mismatch
	 */
	module = Py_InitModule3(
	          "pyfwsi",
	          pyfwsi_module_methods,
	          "Python libfwsi module (pyfwsi)." );

	PyEval_InitThreads();

	gil_state = PyGILState_Ensure();

	/* Setup the item list type object
	 */
	pyfwsi_item_list_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwsi_item_list_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwsi_item_list_type_object );

	item_list_type_object = &pyfwsi_item_list_type_object;

	PyModule_AddObject(
	 module,
	 "item_list",
	 (PyObject *) item_list_type_object );

	/* Setup the item type object
	 */
	pyfwsi_item_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwsi_item_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwsi_item_type_object );

	item_type_object = &pyfwsi_item_type_object;

	PyModule_AddObject(
	 module,
	 "item",
	 (PyObject *) item_type_object );

	/* Setup the items type object
	 */
	pyfwsi_items_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwsi_items_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwsi_items_type_object );

	items_type_object = &pyfwsi_items_type_object;

	PyModule_AddObject(
	 module,
	 "_items",
	 (PyObject *) items_type_object );

	/* Setup the root folder type object
	 */
	pyfwsi_root_folder_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwsi_root_folder_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwsi_root_folder_type_object );

	root_folder_type_object = &pyfwsi_root_folder_type_object;

	PyModule_AddObject(
	 module,
	 "root_folder",
	 (PyObject *) root_folder_type_object );

	/* Setup the volume type object
	 */
	pyfwsi_volume_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwsi_volume_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwsi_volume_type_object );

	volume_type_object = &pyfwsi_volume_type_object;

	PyModule_AddObject(
	 module,
	 "volume",
	 (PyObject *) volume_type_object );

	/* Setup the file entry type object
	 */
	pyfwsi_file_entry_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwsi_file_entry_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwsi_file_entry_type_object );

	file_entry_type_object = &pyfwsi_file_entry_type_object;

	PyModule_AddObject(
	 module,
	 "file_entry",
	 (PyObject *) file_entry_type_object );

	/* Setup the network location type object
	 */
	pyfwsi_network_location_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwsi_network_location_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwsi_network_location_type_object );

	network_location_type_object = &pyfwsi_network_location_type_object;

	PyModule_AddObject(
	 module,
	 "network_location",
	 (PyObject *) network_location_type_object );

	/* Setup the extension block type object
	 */
	pyfwsi_extension_block_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwsi_extension_block_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwsi_extension_block_type_object );

	extension_block_type_object = &pyfwsi_extension_block_type_object;

	PyModule_AddObject(
	 module,
	 "extension_block",
	 (PyObject *) extension_block_type_object );

	/* Setup the extension blocks type object
	 */
	pyfwsi_extension_blocks_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwsi_extension_blocks_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwsi_extension_blocks_type_object );

	extension_blocks_type_object = &pyfwsi_extension_blocks_type_object;

	PyModule_AddObject(
	 module,
	 "_extension_blocks",
	 (PyObject *) extension_blocks_type_object );

	/* Setup the file entry extension type object
	 */
	pyfwsi_file_entry_extension_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pyfwsi_file_entry_extension_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pyfwsi_file_entry_extension_type_object );

	file_entry_extension_type_object = &pyfwsi_file_entry_extension_type_object;

	PyModule_AddObject(
	 module,
	 "file_entry_extension",
	 (PyObject *) file_entry_extension_type_object );

on_error:
	PyGILState_Release(
	 gil_state );
}
