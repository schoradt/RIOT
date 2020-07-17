PKG_NAME=gecko_sdk
PKG_URL=https://github.com/schoradt/RIOT-gecko-sdk.git
PKG_VERSION=bd4027a67daa12b8d7044c63f8bb22071e199c6b
PKG_LICENSE=Zlib

include $(RIOTBASE)/pkg/pkg.mk

ifneq ($(CPU),efm32)
  $(error This package can only be used with EFM32 CPUs)
endif

ifneq (llvm,$(TOOLCHAIN))
  CFLAGS += -Wno-int-in-bool-context
endif

all:
	"$(MAKE)" -C $(PKG_SOURCE_DIR)/dist
