/** @file
    @brief Implementation of tool to install a self-signed USB CDC driver
	selectively on old VID/PID pairs, only if they meet certain criteria.

    @date 2015

    @author
    Sensics, Inc.
    <http://sensics.com/osvr>
*/

// Copyright 2015 Sensics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Internal Includes
// - none

// Library/third-party includes
#include "libwdi.h"

// Standard includes
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <string>
#include <iostream>

static const std::string DEVICE_DESC = "OSVR";
static const uint16_t VID = 0x03EB;
static const uint16_t PID = 0x2421;
static const char INF[] = "sensics_generic_cdc.inf";

int main() {
  struct wdi_device_info *device, *list;

  char VENDOR[] = "Sensics, Inc.";
  char CERT_SUBJECT[] = "CN=USB CDC (libwdi autogenerated)";
  wdi_set_log_level(WDI_LOG_LEVEL_ERROR);

  bool gotOne = false;
  if (wdi_create_list(&list, NULL) == WDI_SUCCESS) {
    for (device = list; device != NULL; device = device->next) {
      printf("Found driverless USB device: \"%s\" (%04X:%04X)\n", device->desc,
             device->vid, device->pid);

      if (VID != device->vid || PID != device->pid) {
        // VID or PID not a match
        continue;
      }
      std::string desc(device->desc);
      if (desc.length() < DEVICE_DESC.length()) {
        // Description prefix can't possibly match, too short.
        continue;
      }
      if (desc.substr(0, DEVICE_DESC.length()) != DEVICE_DESC) {
        // Doesn't start with the device desc prefix
        continue;
      }
      // OK, passed the hurdles!
      printf(" - Eligible for update!\n");
	  gotOne = true;
      {
        wdi_options_prepare_driver opts = {0};
        opts.driver_type = WDI_CDC;
        opts.vendor_name = VENDOR;
        opts.disable_cat = FALSE;
        opts.disable_signing = FALSE;
        opts.cert_subject = CERT_SUBJECT;
        opts.use_wcid_driver = FALSE;
        int result = wdi_prepare_driver(device, nullptr, INF, &opts);
        if (WDI_SUCCESS == result) {
          printf(" - Driver extraction succeeded!\n");
        } else {
          printf(" - Driver extraction failed: %s\n", wdi_strerror(result));
          continue;
        }
      }
      {
        int result = wdi_install_driver(device, nullptr, INF, nullptr);
        if (WDI_SUCCESS == result) {
          printf(" - Driver install succeeded!\n");
        } else {
          printf(" - Driver install failed: %s\n", wdi_strerror(result));
        }
      }
    }
    wdi_destroy_list(list);
  }
  if (gotOne) {
	  printf("Press enter to exit...\n");
	  std::cin.ignore();
  }
  return 0;
}