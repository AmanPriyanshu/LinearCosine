from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import sys
import setuptools
import platform

class get_pybind_include(object):
    def __init__(self, user=False):
        self.user = user

    def __str__(self):
        import pybind11
        return pybind11.get_include(self.user)

extra_compile_args = []
extra_link_args = []

if platform.system() == "Darwin": 
    extra_compile_args.append('-std=c++11')
    extra_compile_args.append('-stdlib=libc++')
    extra_link_args.append('-stdlib=libc++')
elif platform.system() == "Linux":
    extra_compile_args.append('-std=c++11')
elif platform.system() == "Windows":
    extra_compile_args.append('/std:c++11')

ext_modules = [
    Extension(
        'linear_cosine._linear_cosine',
        ['src/linear_cosine/_linear_cosine.cpp'],
        include_dirs=[
            get_pybind_include(),
            get_pybind_include(user=True)
        ],
        language='c++',
        extra_compile_args=extra_compile_args,
        extra_link_args=extra_link_args,
    ),
]

# As of Python 3.6, CCompiler has a `has_flag` method.
# cf http://bugs.python.org/issue26689
def has_flag(compiler, flagname):
    """Return a boolean indicating whether a flag name is supported on
    the specified compiler.
    """
    import tempfile
    with tempfile.NamedTemporaryFile('w', suffix='.cpp') as f:
        f.write('int main (int argc, char **argv) { return 0; }')
        try:
            compiler.compile([f.name], extra_postargs=[flagname])
        except setuptools.distutils.errors.CompileError:
            return False
    return True

class BuildExt(build_ext):
    """A custom build extension for adding compiler-specific options."""
    def build_extensions(self):
        if platform.system() == "Windows":
            if has_flag(self.compiler, '/std:c++11'):
                for ext in self.extensions:
                    ext.extra_compile_args.append('/std:c++11')
        build_ext.build_extensions(self)

setup(
    name='LinearCosine',
    version='0.1.0',
    author='Aman Priyanshu',
    author_email='amanpriyanshusms2001@gmail.com',
    description='Adding beats multiplying for lower-precision efficient cosine similarity',
    long_description=open('README.md').read(),
    long_description_content_type='text/markdown',
    url='https://github.com/AmanPriyanshu/LinearCosine',
    packages=['linear_cosine'],
    package_dir={'': 'src'},
    ext_modules=ext_modules,
    install_requires=['pybind11>=2.4'],
    setup_requires=['pybind11>=2.4'],
    cmdclass={'build_ext': BuildExt},
    zip_safe=False,
    python_requires='>=3.9',
)