/*
 * Volume (shell item) functions
 *
 * Copyright (C) 2010-2018, Joachim Metz <joachim.metz@gmail.com>
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
#include <memory.h>
#include <types.h>

#include "libfwsi_definitions.h"
#include "libfwsi_item.h"
#include "libfwsi_libcerror.h"
#include "libfwsi_libuna.h"
#include "libfwsi_volume.h"
#include "libfwsi_volume_values.h"

/* Retrieves the size of the UTF-8 formatted name
 * Returns 1 if successful or -1 on error
 */
int libfwsi_volume_get_utf8_name_size(
     libfwsi_item_t *item,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	libfwsi_internal_item_t *internal_item = NULL;
	libfwsi_volume_values_t *volume_values = NULL;
	static char *function                  = "libfwsi_volume_get_utf8_name_size";

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libfwsi_internal_item_t *) item;

	if( ( internal_item->class_type & 0x70 ) != LIBFWSI_CLASS_TYPE_VOLUME )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported class type.",
		 function );

		return( -1 );
	}
	if( internal_item->value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item - missing value.",
		 function );

		return( -1 );
	}
	volume_values = (libfwsi_volume_values_t *) internal_item->value;

	if( libuna_utf8_string_size_from_byte_stream(
	     volume_values->name,
	     volume_values->name_size,
	     volume_values->ascii_codepage,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 formatted name
 * Returns 1 if successful or -1 on error
 */
int libfwsi_volume_get_utf8_name(
     libfwsi_item_t *item,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	libfwsi_internal_item_t *internal_item = NULL;
	libfwsi_volume_values_t *volume_values = NULL;
	static char *function                  = "libfwsi_volume_get_utf8_name";

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libfwsi_internal_item_t *) item;

	if( ( internal_item->class_type & 0x70 ) != LIBFWSI_CLASS_TYPE_VOLUME )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported class type.",
		 function );

		return( -1 );
	}
	if( internal_item->value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item - missing value.",
		 function );

		return( -1 );
	}
	volume_values = (libfwsi_volume_values_t *) internal_item->value;

	if( libuna_utf8_string_copy_from_byte_stream(
	     utf8_string,
	     utf8_string_size,
	     volume_values->name,
	     volume_values->name_size,
	     volume_values->ascii_codepage,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 formatted name
 * Returns 1 if successful or -1 on error
 */
int libfwsi_volume_get_utf16_name_size(
     libfwsi_item_t *item,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	libfwsi_internal_item_t *internal_item = NULL;
	libfwsi_volume_values_t *volume_values = NULL;
	static char *function                  = "libfwsi_volume_get_utf16_name_size";

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libfwsi_internal_item_t *) item;

	if( ( internal_item->class_type & 0x70 ) != LIBFWSI_CLASS_TYPE_VOLUME )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported class type.",
		 function );

		return( -1 );
	}
	if( internal_item->value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item - missing value.",
		 function );

		return( -1 );
	}
	volume_values = (libfwsi_volume_values_t *) internal_item->value;

	if( libuna_utf16_string_size_from_byte_stream(
	     volume_values->name,
	     volume_values->name_size,
	     volume_values->ascii_codepage,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 formatted name
 * Returns 1 if successful or -1 on error
 */
int libfwsi_volume_get_utf16_name(
     libfwsi_item_t *item,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	libfwsi_internal_item_t *internal_item = NULL;
	libfwsi_volume_values_t *volume_values = NULL;
	static char *function                  = "libfwsi_volume_get_utf16_name";

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libfwsi_internal_item_t *) item;

	if( ( internal_item->class_type & 0x70 ) != LIBFWSI_CLASS_TYPE_VOLUME )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported class type.",
		 function );

		return( -1 );
	}
	if( internal_item->value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item - missing value.",
		 function );

		return( -1 );
	}
	volume_values = (libfwsi_volume_values_t *) internal_item->value;

	if( libuna_utf16_string_copy_from_byte_stream(
	     utf16_string,
	     utf16_string_size,
	     volume_values->name,
	     volume_values->name_size,
	     volume_values->ascii_codepage,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the identifier
 * The identifier is a GUID and is 16 bytes of size
 * Returns 1 if successful or -1 on error
 */
int libfwsi_volume_get_identifier(
     libfwsi_item_t *item,
     uint8_t *identifier,
     size_t size,
     libcerror_error_t **error )
{
	libfwsi_internal_item_t *internal_item = NULL;
	libfwsi_volume_values_t *volume_values = NULL;
	static char *function                  = "libfwsi_volume_get_identifier";

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libfwsi_internal_item_t *) item;

	if( ( internal_item->class_type & 0x70 ) != LIBFWSI_CLASS_TYPE_VOLUME )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported class type.",
		 function );

		return( -1 );
	}
	if( internal_item->value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item - missing value.",
		 function );

		return( -1 );
	}
	volume_values = (libfwsi_volume_values_t *) internal_item->value;

	if( identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid identifier.",
		 function );

		return( -1 );
	}
	if( size < 16 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: identifier too small.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     identifier,
	     volume_values->identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the shell folder identifier
 * The identifier is a GUID and is 16 bytes of size
 * Returns 1 if successful or -1 on error
 */
int libfwsi_volume_get_shell_folder_identifier(
     libfwsi_item_t *item,
     uint8_t *shell_folder_identifier,
     size_t size,
     libcerror_error_t **error )
{
	libfwsi_internal_item_t *internal_item = NULL;
	libfwsi_volume_values_t *volume_values = NULL;
	static char *function                  = "libfwsi_volume_get_shell_folder_identifier";

	if( item == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item.",
		 function );

		return( -1 );
	}
	internal_item = (libfwsi_internal_item_t *) item;

	if( ( internal_item->class_type & 0x70 ) != LIBFWSI_CLASS_TYPE_VOLUME )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported class type.",
		 function );

		return( -1 );
	}
	if( internal_item->value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid item - missing value.",
		 function );

		return( -1 );
	}
	volume_values = (libfwsi_volume_values_t *) internal_item->value;

	if( shell_folder_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid shell folder identifier.",
		 function );

		return( -1 );
	}
	if( size < 16 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: shell folder identifier too small.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     shell_folder_identifier,
	     volume_values->shell_folder_identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy shell folder identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

