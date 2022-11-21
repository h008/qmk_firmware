#!/usr/bin/bash
sudo dfu-util -D planck_rev6_h008.bin -d 0483:dfqq -a 0 -s 0x08000000:leave
