##############################################################################
#
#     daisy.gypi
#     Copyright (c) 2020 Raphael DINGE
#
#Tab=3########################################################################



{
   'target_defaults': {
      'configurations':
      {
         'Debug':
         {
            'defines': [
               'DEBUG=1',
            ],

            'cflags': [
               '-O0',
               '-g',
            ],
         },

         'Release':
         {
            'defines': [
               'NDEBUG=1',
               'RELEASE=1',
            ],

            'cflags': [
               '-O3',
            ],
         },
      },

      'defines': [
         'CORE_CM7',
         'STM32H750xx',
         'STM32H750IB',
         'ARM_MATH_CM7',
         'flash_layout',
         'HSE_VALUE=16000000',
         'USE_HAL_DRIVER',
         'USE_FULL_LL_DRIVER',
      ],

      'cflags': [
         '-mthumb',
         '-mfloat-abi=hard',
         '-mfpu=fpv5-d16',
         '-mcpu=cortex-m7',

         '-fasm',
         '-fdata-sections',
         '-ffunction-sections',

         '-finline',
         '-finline-functions-called-once',
         '-fshort-enums',
         '-fno-move-loop-invariants',

         '-Wall',
         '-Wextra',
         '-Wpedantic',
         '-Werror',
      ],

      'cflags_c': [
         '-std=gnu11',
      ],

      'cflags_cc': [
         '-std=gnu++2a',
         '-fno-exceptions',
         '-fno-rtti',
         '-fno-unwind-tables',

         '-Wno-register',
         '-Wno-volatile',
      ],

      'ldflags': [
         '-mthumb',
         '-mfloat-abi=hard',
         '-mfpu=fpv5-d16',
         '-mcpu=cortex-m7',

         '--specs=nano.specs',
         '--specs=nosys.specs',

         '-lc',
         '-lm',
         '-lnosys',

         '-Wl,-Map=out.map,--cref',
         '-Wl,--gc-sections',
      ],
   },
}
