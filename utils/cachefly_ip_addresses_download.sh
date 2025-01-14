#!/usr/bin/env bash

set -e

cd "$(dirname "${0}")" || exit 1
. ./common.sh || exit 1

DEST=../src/lib/inc_generated/ndpi_cachefly_match.c.inc
LIST=/tmp/cachefly.list
ORIGIN='https://cachefly.cachefly.net/ips/cdn.txt'
#TODO: ipv6. Is there any ipv6 list?

echo "(1) Downloading file..."
http_response=$(curl -s -o "${LIST}" -w "%{http_code}" "${ORIGIN}")
check_http_response "${http_response}"
is_file_empty "${LIST}"

echo "(2) Processing IP addresses..."
./ipaddr2list.py "${LIST}" NDPI_PROTOCOL_CACHEFLY > "${DEST}"
rm -f "${LIST}"
is_file_empty "${DEST}"

echo "(3) Cachefly IPs are available in ${DEST}"
exit 0
