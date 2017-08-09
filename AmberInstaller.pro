#-------------------------------------------------
#
# Project created by QtCreator 2017-08-06T11:13:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AmberInstaller
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += ./lib/zlib/libz.a

INCLUDEPATH += ./lib/libzip \
    ./lib/libzip/gladman-fcrypt

SOURCES += main.cpp\
        mainwidget.cpp \
    lib/libzip/gladman-fcrypt/aescrypt.c \
    lib/libzip/gladman-fcrypt/aeskey.c \
    lib/libzip/gladman-fcrypt/aestab.c \
    lib/libzip/gladman-fcrypt/fileenc.c \
    lib/libzip/gladman-fcrypt/hmac.c \
    lib/libzip/gladman-fcrypt/pwd2key.c \
    lib/libzip/gladman-fcrypt/sha1.c \
    lib/libzip/gladman-fcrypt.c \
    lib/libzip/mkstemp.c \
    lib/libzip/zip_add.c \
    lib/libzip/zip_add_dir.c \
    lib/libzip/zip_add_entry.c \
    lib/libzip/zip_buffer.c \
    lib/libzip/zip_close.c \
    lib/libzip/zip_delete.c \
    lib/libzip/zip_dir_add.c \
    lib/libzip/zip_dirent.c \
    lib/libzip/zip_discard.c \
    lib/libzip/zip_entry.c \
    lib/libzip/zip_err_str.c \
    lib/libzip/zip_error.c \
    lib/libzip/zip_error_clear.c \
    lib/libzip/zip_error_get.c \
    lib/libzip/zip_error_get_sys_type.c \
    lib/libzip/zip_error_strerror.c \
    lib/libzip/zip_error_to_str.c \
    lib/libzip/zip_extra_field.c \
    lib/libzip/zip_extra_field_api.c \
    lib/libzip/zip_fclose.c \
    lib/libzip/zip_fdopen.c \
    lib/libzip/zip_file_add.c \
    lib/libzip/zip_file_error_clear.c \
    lib/libzip/zip_file_error_get.c \
    lib/libzip/zip_file_get_comment.c \
    lib/libzip/zip_file_get_external_attributes.c \
    lib/libzip/zip_file_get_offset.c \
    lib/libzip/zip_file_rename.c \
    lib/libzip/zip_file_replace.c \
    lib/libzip/zip_file_set_comment.c \
    lib/libzip/zip_file_set_encryption.c \
    lib/libzip/zip_file_set_external_attributes.c \
    lib/libzip/zip_file_set_mtime.c \
    lib/libzip/zip_file_strerror.c \
    lib/libzip/zip_filerange_crc.c \
    lib/libzip/zip_fopen.c \
    lib/libzip/zip_fopen_encrypted.c \
    lib/libzip/zip_fopen_index.c \
    lib/libzip/zip_fopen_index_encrypted.c \
    lib/libzip/zip_fread.c \
    lib/libzip/zip_fseek.c \
    lib/libzip/zip_ftell.c \
    lib/libzip/zip_get_archive_comment.c \
    lib/libzip/zip_get_archive_flag.c \
    lib/libzip/zip_get_compression_implementation.c \
    lib/libzip/zip_get_encryption_implementation.c \
    lib/libzip/zip_get_file_comment.c \
    lib/libzip/zip_get_name.c \
    lib/libzip/zip_get_num_entries.c \
    lib/libzip/zip_get_num_files.c \
    lib/libzip/zip_hash.c \
    lib/libzip/zip_io_util.c \
    lib/libzip/zip_memdup.c \
    lib/libzip/zip_name_locate.c \
    lib/libzip/zip_new.c \
    lib/libzip/zip_open.c \
    lib/libzip/zip_random_win32.c \
    lib/libzip/zip_rename.c \
    lib/libzip/zip_replace.c \
    lib/libzip/zip_set_archive_comment.c \
    lib/libzip/zip_set_archive_flag.c \
    lib/libzip/zip_set_default_password.c \
    lib/libzip/zip_set_file_comment.c \
    lib/libzip/zip_set_file_compression.c \
    lib/libzip/zip_set_name.c \
    lib/libzip/zip_source_begin_write.c \
    lib/libzip/zip_source_buffer.c \
    lib/libzip/zip_source_call.c \
    lib/libzip/zip_source_close.c \
    lib/libzip/zip_source_commit_write.c \
    lib/libzip/zip_source_crc.c \
    lib/libzip/zip_source_deflate.c \
    lib/libzip/zip_source_error.c \
    lib/libzip/zip_source_filep.c \
    lib/libzip/zip_source_free.c \
    lib/libzip/zip_source_function.c \
    lib/libzip/zip_source_is_deleted.c \
    lib/libzip/zip_source_layered.c \
    lib/libzip/zip_source_open.c \
    lib/libzip/zip_source_pkware.c \
    lib/libzip/zip_source_read.c \
    lib/libzip/zip_source_remove.c \
    lib/libzip/zip_source_rollback_write.c \
    lib/libzip/zip_source_seek.c \
    lib/libzip/zip_source_seek_write.c \
    lib/libzip/zip_source_stat.c \
    lib/libzip/zip_source_supports.c \
    lib/libzip/zip_source_tell.c \
    lib/libzip/zip_source_tell_write.c \
    lib/libzip/zip_source_win32a.c \
    lib/libzip/zip_source_win32handle.c \
    lib/libzip/zip_source_win32utf8.c \
    lib/libzip/zip_source_win32w.c \
    lib/libzip/zip_source_window.c \
    lib/libzip/zip_source_winzip_aes_decode.c \
    lib/libzip/zip_source_winzip_aes_encode.c \
    lib/libzip/zip_source_write.c \
    lib/libzip/zip_source_zip.c \
    lib/libzip/zip_source_zip_new.c \
    lib/libzip/zip_stat.c \
    lib/libzip/zip_stat_index.c \
    lib/libzip/zip_stat_init.c \
    lib/libzip/zip_strerror.c \
    lib/libzip/zip_string.c \
    lib/libzip/zip_unchange.c \
    lib/libzip/zip_unchange_all.c \
    lib/libzip/zip_unchange_archive.c \
    lib/libzip/zip_unchange_data.c \
    lib/libzip/zip_utf-8.c \
    zipfile.cpp

HEADERS  += mainwidget.h \
    lib/libzip/gladman-fcrypt/aes.h \
    lib/libzip/gladman-fcrypt/aesopt.h \
    lib/libzip/gladman-fcrypt/fileenc.h \
    lib/libzip/gladman-fcrypt/hmac.h \
    lib/libzip/gladman-fcrypt/pwd2key.h \
    lib/libzip/gladman-fcrypt/sha1.h \
    lib/libzip/compat.h \
    lib/libzip/config.h \
    lib/libzip/gladman-fcrypt.h \
    lib/libzip/zip.h \
    lib/libzip/zipconf.h \
    lib/libzip/zipint.h \
    lib/libzip/zipwin32.h \
    lib/zlib/zconf.h \
    lib/zlib/zlib.h \
    zipfile.h

FORMS    += mainwidget.ui

RESOURCES += \
    resource.qrc

RC_FILE += ./res/window_resource.rc

DISTFILES += \
    res/window_resource.rc
