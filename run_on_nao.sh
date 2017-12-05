#!/usr/bin/env bash
NAO_IP=128.39.75.111

scp build*/sdk/bin/a nao@${NAO_IP}:~/
ssh nao@${NAO_IP}  "~/./a"
