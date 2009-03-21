/*
 * Copyright (C) 2009 Niek Linnenbank
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <api/VMCopy.h>
#include <string.h>
#include "TmpFile.h"

TmpFile::TmpFile() : buffer(ZERO), size(ZERO)
{
}

TmpFile::~TmpFile()
{
    if (buffer)	delete buffer;
}

Error TmpFile::read(FileSystemMessage *msg)
{
    Size bytes;

    /* Bounds checking. */
    if (msg->offset >= size)
    {
	return 0;
    }
    else
	bytes = size - msg->offset > msg->size ? msg->size : size - msg->offset;
    
    /* Copy the buffers. */
    return VMCopy(msg->procID, Write, (Address) buffer + msg->offset,
				      (Address) msg->buffer, bytes);
}

Error TmpFile::write(FileSystemMessage *msg)
{
    return EACCESS;
}
