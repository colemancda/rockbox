/* Copyright (c) 2009, Christophe Fergeau  <teuf@gnome.org>
 *
 * The code contained in this file is free software; you can redistribute
 * it and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either version
 * 2.1 of the License, or (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this code; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#define _XOPEN_SOURCE /* to enable strptime() */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

extern int sync_time (const char *dev, struct tm *tm);
extern char *basename (char *__filename);

int
main (int argc, char **argv)
{
    if (argc < 2) {
        printf ("usage: %s <device> [time]\n", basename(argv[0]));
        return 1;
    }

    struct tm time;
    struct tm* ptime = NULL;
    if (argc > 2) {
        if(strptime(argv[2], "%Y-%m-%dT%H:%M:%S", &time)) {
            ptime = &time;
        }
        else {
            printf ("Could not parse time. Using local time.\n");
            printf ("Time string needs to use the format YYYY-MM-DDThh:mm:ss\n");
            printf ("(ISO 8601 format)\n");
        }
    }

    if (sync_time (argv[1], ptime)) {
        printf ("Error occured while syncing time.\n");
    } else {
        printf ("Time was synced!\n");
    }

    return 0;
}
