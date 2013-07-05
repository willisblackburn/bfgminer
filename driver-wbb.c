#include "miner.h"
#include "fpgautils.h"
#include "driver-wbb.h"

static int wbb_autodetect() {

	struct cgpu_info *cgpu = calloc(1, sizeof(struct cgpu_info));
	if (unlikely(!cgpu))
		quit(1, "Failed to calloc cgpu_info for WBB driver");
	cgpu->drv = &wbb_drv;
	cgpu->devtype = "WBB";
	cgpu->deven = DEV_ENABLED;
	cgpu->threads = 1;
	cgpu->kname = "Willis Blackburn";
	add_cgpu(cgpu);

	return 1;
}

static void wbb_detect() {

  RUNONCE();

  noserial_detect(&wbb_drv, wbb_autodetect);
}

struct device_drv wbb_drv = {
  .dname = "wbb",
  .name = "WBB",
  .drv_detect = wbb_detect,
};
