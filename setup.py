from setuptools import Extension, setup

setup(
        name='adclib',
        version='0.1',
        ext_modules=[Extension(name='adc', sources=['adc.c'], extra_link_args=['-le502api', '-lx502api'])],
        
)

print('setup')
