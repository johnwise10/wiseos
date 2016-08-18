#!/bin/sh

if grub-file --is-x86-multiboot wsImage; then
  echo multiboot confirmed
else
  echo the file is not multiboot
fi
