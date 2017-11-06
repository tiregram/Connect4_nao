#!/usr/bin/env bash

scp build*/sdk/bin/a nao@${NAO_IP}:~/
ssh nao@${NAO_IP}  "~/./a"
