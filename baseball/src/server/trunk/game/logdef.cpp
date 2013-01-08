#include "logdef.h"

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

/* -------------------------------------------------------------------------- */

MSG::Log<boost::detail::lightweight_mutex,
		boost::detail::lightweight_mutex::scoped_lock> baseball_logger("baseball_game.log");

/* -------------------------------------------------------------------------- */
