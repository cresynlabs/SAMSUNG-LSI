#include <stdlib.h>
#include "main.h"
#include "wpc.h"
#include "wpc_common.h"
#include "sc_drv.h"
#include "fg_drv.h"
#include "common_drv.h"

struct wpt_data *wpt_info;

void WPTProcess(struct wpt_data *wpt)
{
}

struct wpt_data *wpt_main_init(void)
{
	struct wpt_data *wpt;

	wpt = malloc(sizeof(struct wpt_data));
	if (!wpt)
	{
		printf("%s, failed to allocate WPT driver data\r\n", __func__);
		return wpt;
	}

	wpt_info = wpt;

	return wpt;
}
