/*
  Copyright 2016-2018 Jyri J. Virkki <jyri@virkki.com>

  This file is part of dupd.

  dupd is free software: you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  dupd is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with dupd.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _DUPD_READLIST_H
#define _DUPD_READLIST_H

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>

struct read_list_entry {
  struct path_list_head * pathlist_head;
  struct path_list_entry * pathlist_self;
#ifdef USE_FIEMAP
  uint64_t block;
#endif
  dev_t device;
  ino_t inode;
};

extern struct read_list_entry * read_list;
extern long read_list_end;


/** ***************************************************************************
 * Initialize read list.
 *
 * Parameters: none
 *
 * Return: none
 *
 */
void init_read_list();


/** ***************************************************************************
 * Free read list.
 *
 * Parameters: none
 *
 * Return: none
 *
 */
void free_read_list();


/** ***************************************************************************
 * Add a file to the read list.
 *
 * Parameters:
 *    block  - First physical block of file (zero if not used).
 *    inode  - The inode of this file.
 *    head   - Pointer to the head of the path list which contains this file.
 *    entry  - Pointer to path list entry corresponding to this file.
 *
 * Return: none
 *
 */
void add_to_read_list(uint64_t block, ino_t inode,
                      struct path_list_head * head,
                      struct path_list_entry * entry);


/** ***************************************************************************
 * Sort the read list.
 *
 * If hardlink_is_unique, also removes duplicate inodes from the list.
 *
 * Parameters:
 *    use_block - Sort by block instead of inode (only relevant if USE_FIEMAP).
 *
 * Return: none
 *
 */
void sort_read_list(int use_block);


#endif
