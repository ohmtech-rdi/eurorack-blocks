# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
# import os
# import sys
# sys.path.insert(0, os.path.abspath('.'))


# -- Project information -----------------------------------------------------

project = 'Eurorack-blocks'
copyright = '2022, Raphael Dingé'
author = 'Raphael Dingé'


# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
   'myst_parser',
   'sphinxcontrib.youtube',
]

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']


# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'sphinx_rtd_theme'
html_logo = 'img/logo.svg'
html_theme_options = {
   'logo_only': True,
   'display_version': False,
}

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']
html_css_files = ['css/custom.css']

myst_enable_extensions = [
   'deflist',
]



# -- Pygments Lexers ---------------------------------------------------------

from pygments.lexer import RegexLexer, words
from pygments import token
from sphinx.highlighting import lexers

class ErbbLexer(RegexLexer):
   name = 'erbb'

   tokens = {
      'root': [
         (r'//.*?$', token.Comment.Singleline),
         (r'\".*\"', token.Literal.String),
         (r'module|file|import|define|base|section|resources|sources|data|stream|faust|address|bind|init|use|strict', token.Keyword),
         (r'flash|qspi|mono|interleaved|planar', token.Name.Builtin),
         (r'AudioSample', token.Keyword.Type),
         (r'{|}|=', token.Punctuation),
         (r'(?!\b({})\b)([a-zA-Z]\w*)', token.Name.Variable.Class),
         (r'.', token.Text),
      ],
   }

lexers ['erbb'] = ErbbLexer (startinline=True)


class ErbuiLexer(RegexLexer):
   name = 'erbui'

   tokens = {
      'root': [
         (r'//.*?$', token.Comment.Singleline),
         (r'\".*\"', token.Literal.String),
         (r'[0-9\.]+°cw', token.Literal.Number),
         (r'[0-9\.]+°ccw', token.Literal.Number),
         (r'[0-9\.]+°', token.Literal.Number),
         (r'[0-9\.]+hp', token.Literal.Number),
         (r'[0-9\.]+mm', token.Literal.Number),
         (r'[0-9\.]+cm', token.Literal.Number),
         (r'[0-9\.]+', token.Literal.Number),
         (r'module|board|width|material|header|footer|line|control|label|sticker|image|pin|pins|cascade|mode|positioning|position|rotation|offset|style|route|faust|address|bind|init|value|property|exclude|extends|alias|file|class|include|pcb|type|gpio|pwm|dac', token.Keyword),
         (r'center|left|top|right|bottom|normalized|bipolar|wire|manual|natural|black|white|aluminum|brushed_aluminum|aluminum_coated', token.Name.Builtin),
         (r'rogan.6ps|rogan.5ps|rogan.3ps|rogan.2ps|rogan.1ps|rogan.2s.black|rogan.1s|rogan.1s.black|songhuei.9mm|dailywell.2ms1|dailywell.2ms3|led.3mm.green_red|led.3mm.rgb|led.3mm.red|led.3mm.green|led.3mm.yellow|led.3mm.orange|thonk.pj398sm.knurled|thonk.pj398sm.hex|tl1105|ck.d6r.black', token.Name.Builtin),
         (r'AudioIn|AudioOut|Button|CvIn|CvOut|Encoder|GateIn|GateOut|LedBi|LedRgb|Led|Pot|Switch|Trim', token.Keyword.Type),
         (r'{|}|,', token.Punctuation),
         (r'(?!\b({})\b)([a-zA-Z]\w*)', token.Name.Variable.Class),
         (r'.', token.Text),
      ],
   }

lexers ['erbui'] = ErbuiLexer (startinline=True)
