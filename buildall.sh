#!/bin/sh

ls Make* | xargs -I{} make -f {}
