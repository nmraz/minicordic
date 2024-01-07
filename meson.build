project('cordic', 'c')

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required : true)
executable('cordic', 'cordic.c', dependencies: m_dep)
