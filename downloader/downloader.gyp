{
  'targets': [
    {
      'target_name': 'downloader',
      'type': 'executable',
      'sources': [
        'downloader_main.cc',
      ],
      'include_dirs': [
        '<(DEPTH)',
      ],
      'dependencies': [
        '../base/base.gyp:base',
        '../base/base.gyp:base_i18n',
        '../ui/base/ui_base.gyp:ui_base',
        '../ui/compositor/compositor.gyp:compositor',
        '../ui/compositor/compositor.gyp:compositor_test_support',
        '../ui/gfx/gfx.gyp:gfx',
        '../ui/views/views.gyp:views',
        '../ui/views/views.gyp:views_test_support',
        'downloader_lib',
        'repack_downloader_resources',
      ],
    },  # target_name: downloader
    {
      'target_name': 'downloader_lib',
      'type': 'static_library',
      'sources': [
        'downloader_export.h',
        'downloader_window.cc',
        'downloader_window.h',
        'main_contents.cc',
        'main_contents.h',
        'menu_view.cc',
        'menu_view.h',
        'toolbar_button.cc',
        'toolbar_button.h',
        'toolbar_view.cc',
        'toolbar_view.h',
      ],
      'include_dirs': [
        '<(DEPTH)',
      ],
      'defines': [
        "GFX_VECTOR_ICONS_UNSAFE",
        "AURA_IMPLEMENTATION",
      ],
      'dependencies': [
        '../base/base.gyp:base',
        '../skia/skia.gyp:skia',
        '../third_party/icu/icu.gyp:icui18n',
        '../third_party/icu/icu.gyp:icuuc',
        '../ui/base/ui_base.gyp:ui_base',
        '../ui/events/events.gyp:events',
        '../ui/gfx/gfx.gyp:gfx',
        '../ui/gfx/gfx.gyp:gfx_geometry',
        '../ui/gfx/gfx.gyp:gfx_vector_icons',
      ],
    },  # target_name: downloader_lib
    {
      'target_name': 'downloader_resources',
      'type': 'none',
      'variables': {
        'grit_out_dir': '<(SHARED_INTERMEDIATE_DIR)/downloader',
        'grit_resource_ids': '../tools/gritsettings/resource_ids',
      },
      'actions': [
        {
          'action_name': 'downloader_images',
          'variables': {
            'grit_grd_file': 'downloader_images_resources.grd',
          },
          'includes': [ '../build/grit_action.gypi' ],
        },
        {
          'action_name': 'downloader_strings',
          'variables': {
            'grit_grd_file': 'downloader_strings.grd',
          },
          'includes': [ '../build/grit_action.gypi' ],
        },
      ],
    },  # target_name: downloader_images
    {
      'target_name': 'repack_downloader_resources',
      'type': 'none',
      'dependencies': [
        'downloader_resources',
        '../ui/app_list/resources/app_list_resources.gyp:app_list_resources',
        '../ui/resources/ui_resources.gyp:ui_resources',
      ],
      'actions': [
        {
          'action_name': 'repack_downloader_resorces',
          'variables': {
            'pak_inputs': [
              '<(SHARED_INTERMEDIATE_DIR)/downloader/downloader_images_resources.pak',
              '<(SHARED_INTERMEDIATE_DIR)/downloader/downloader_strings.pak',
              '<(SHARED_INTERMEDIATE_DIR)/ui/resources/ui_resources_100_percent.pak',
            ],
            'pak_output': '<(PRODUCT_DIR)/downloader_resources.pak',
            'conditions': [
              # ['enable_app_list==1', {
              #   'pak_inputs': [
              #     '<(SHARED_INTERMEDIATE_DIR)/ui/app_list/resources/app_list_resources_100_percent.pak',
              #   ],
              # }],
            ],
          },
          'includes': [ '../build/repack_action.gypi' ],
        },
        {
          'action_name': 'repack_locales_pack',
          'variables': {
            'grit_out_dir': '<(SHARED_INTERMEDIATE_DIR)/downloader',
            'pak_locales': '<(locales)',
          },
          'includes': [ 'downloader_repack_locales.gypi' ],
        },
      ],
      'copies': [
        {
          'destination': '<(PRODUCT_DIR)/locales',
          'files': [
            '<(SHARED_INTERMEDIATE_DIR)/repack/en-US.pak',
            '<(SHARED_INTERMEDIATE_DIR)/repack/zh-CN.pak',
          ],
        },
      ],
    },  # target_name: repack_downloader_resorces
  ]
}
