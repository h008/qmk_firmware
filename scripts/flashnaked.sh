#!/usr/bin/bash
qmk compile -kb salicylic_acid3/naked48 -km h008
qmk flash -kb salicylic_acid3/naked48 -km h008 -bl dfu
