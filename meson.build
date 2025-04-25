project('kraken-jam',
    ['c', 'cpp'],)
deps = [
    dependency('sdl2'),
    dependency('SDL2_image'),
    dependency('SDL2_ttf'),
    dependency('SDL2_mixer'),
    dependency('pugixml'),
]

subdir('src')
incs = include_directories('include')
cc = meson.get_compiler('c')

executable('main',
    ['main.cpp']+sources,
    dependencies: deps,
    include_directories : incs,)
