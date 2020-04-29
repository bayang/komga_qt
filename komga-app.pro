TEMPLATE = subdirs

SUBDIRS += \
    komga_api \
    komga_ui

komga_ui.depends = komga_api
message(kom project dir: $${PWD})
