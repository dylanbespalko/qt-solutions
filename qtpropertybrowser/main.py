import sys
from enum import Enum, Flag, auto, unique

import numpy as np
from PySide2.QtCore import Qt, QDate, QDateTime, QTime, QLocale, QPoint, QPointF, QSize, QSizeF, QRect, QRectF
from PySide2.QtGui import QCursor, QColor, QFont, QKeySequence
from PySide2.QtWidgets import QSizePolicy
from PySide2.QtWidgets import QApplication, QDialog, QLabel, QGridLayout, QScrollArea

from qtpropertybrowser import QtTreePropertyBrowser, QtGroupBoxPropertyBrowser, QtButtonPropertyBrowser
from qtpropertybrowser import QtBoolPropertyManager, QtIntPropertyManager, QtDoublePropertyManager  #, QtComplexPropertyManager
from qtpropertybrowser import QtStringPropertyManager, QtEnumPropertyManager, QtFlagPropertyManager
#from qtpropertybrowser import QtFilePathManager
#from qtpropertybrowser import QtComplexArrayPropertyManager
from qtpropertybrowser import QtDatePropertyManager, QtDateTimePropertyManager, QtTimePropertyManager
from qtpropertybrowser import QtLocalePropertyManager
from qtpropertybrowser import QtPointPropertyManager, QtPointFPropertyManager
from qtpropertybrowser import QtSizePropertyManager, QtSizeFPropertyManager
from qtpropertybrowser import QtRectPropertyManager, QtRectFPropertyManager
from qtpropertybrowser import QtCursorPropertyManager, QtColorPropertyManager, QtFontPropertyManager, QtKeySequencePropertyManager
from qtpropertybrowser import QtSizePolicyPropertyManager
from qtpropertybrowser import QtCheckBoxFactory, QtEnumEditorFactory
from qtpropertybrowser import QtIntEditFactory, QtSpinBoxFactory, QtSliderFactory, QtScrollBarFactory
from qtpropertybrowser import QtLineEditFactory
#from qtpropertybrowser import QtFileEditorFactory
from qtpropertybrowser import QtDoubleEditFactory, QtDoubleSpinBoxFactory  #, QtComplexEditFactory, QtArrayEditFactory
from qtpropertybrowser import QtDateEditFactory, QtDateTimeEditFactory, QtTimeEditFactory
from qtpropertybrowser import QtCursorEditorFactory, QtColorEditorFactory, QtFontEditorFactory
from qtpropertybrowser import QtKeySequenceEditorFactory
from qtpropertybrowser import PkAvg, Scale, Format, Domain, Attribute


@unique
class Color(Enum):
    RED = 0
    GREEN = 1
    BLUE = 2


@unique
class ColorCombiner(Flag):
    BLACK = 0
    RED = auto()
    YELLOW = auto()
    BLUE = auto()
    GREEN = YELLOW | BLUE
    ORANGE = RED | YELLOW
    PURPLE = RED | BLUE
    WHITE = RED | YELLOW | BLUE


def set_value(property_, value):
    print("Set Value of: %s" % (property_.propertyManager(),))


if __name__ == "__main__":
    app = QApplication(sys.argv)
    dialog = QDialog()
    layout = QGridLayout()
    for count in range(1):
        tree_scroll_area = QScrollArea()
        tree_browser = QtTreePropertyBrowser()
        tree_browser.setAttributes([Attribute.PKAVG, Attribute.UNIT, Attribute.FORMAT, Attribute.CHECK])
        box_scroll_area = QScrollArea()
        box_browser = QtGroupBoxPropertyBrowser()
        box_browser.setAttributes([Attribute.MINIMUM, Attribute.MAXIMUM, Attribute.CHECK])
        button_scroll_area = QScrollArea()
        button_browser = QtButtonPropertyBrowser()

        manager_map = {'bool': QtBoolPropertyManager(),
                       'flag': QtFlagPropertyManager(),
                       'enum': QtEnumPropertyManager(),
                       'int': QtIntPropertyManager(),
                       'int2': QtIntPropertyManager(),
                       'int3': QtIntPropertyManager(),
                       'int4': QtIntPropertyManager(),
                       'float': QtDoublePropertyManager(),
                       #'complex': QtComplexPropertyManager(),
                       #'array': QtComplexArrayPropertyManager(),
                       'str': QtStringPropertyManager(),
                       #'tb_file': QtFilePathManager(),
                       #'file': QtFilePathManager(),
                       'date': QtDatePropertyManager(),
                       'datetime': QtDateTimePropertyManager(),
                       'time': QtTimePropertyManager(),
                       'locale': QtLocalePropertyManager(),
                       'point': QtPointPropertyManager(),
                       'pointf': QtPointFPropertyManager(),
                       'size': QtSizePropertyManager(),
                       'sizef': QtSizeFPropertyManager(),
                       'rect': QtRectPropertyManager(),
                       'rectf': QtRectFPropertyManager(),
                       'cursor': QtCursorPropertyManager(),
                       'color': QtColorPropertyManager(),
                       'font': QtFontPropertyManager(),
                       'key_sequence': QtKeySequencePropertyManager(),
                       'size_policy': QtSizePolicyPropertyManager(),
                       }
        factory_map = {'bool': QtCheckBoxFactory(),
                       'enum': QtEnumEditorFactory(),
                       'flag': False,
                       'int': QtIntEditFactory(),
                       'int2': QtSpinBoxFactory(),
                       'int3': QtSliderFactory(),
                       'int4': QtScrollBarFactory(),
                       'float': QtDoubleEditFactory(),
                       'float2': QtDoubleSpinBoxFactory(),
                       #'complex': QtComplexEditFactory(),
                       #'array': QtArrayEditFactory(),
                       'str': QtLineEditFactory(),
                       #'tb_file': QtFileEditorFactory(),
                       #'file': QtFileEditorFactory(),
                       'date': QtDateEditFactory(),
                       'datetime': QtDateTimeEditFactory(),
                       'time': QtTimeEditFactory(),
                       'locale': None,
                       'point': None,
                       'pointf': None,
                       'size': None,
                       'sizef': None,
                       'rect': None,
                       'rectf': None,
                       'cursor': QtCursorEditorFactory(),
                       'color': QtColorEditorFactory(),
                       'font': QtFontEditorFactory(),
                       'key_sequence': QtKeySequenceEditorFactory(),
                       'size_policy': None,
                       }

        # bool
        manager_map['bool'].valueChanged.connect(set_value)
        property_ = manager_map['bool'].addProperty("bool")
        property_.propertyManager().setValue(property_, False)
        tree_browser.setFactoryForManager(manager_map['bool'], factory_map['bool'])
        box_browser.setFactoryForManager(manager_map['bool'], factory_map['bool'])
        button_browser.setFactoryForManager(manager_map['bool'], factory_map['bool'])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # int_read
        manager_map['int'].valueChanged.connect(set_value)
        property_ = manager_map['int'].addProperty("int_read")
        property_.propertyManager().setReadOnly(property_, True)
        property_.propertyManager().setUnit(property_, "V")
        property_.propertyManager().setMinimum(property_, 0)
        property_.propertyManager().setMaximum(property_, 2)
        property_.propertyManager().setValue(property_, 3)
        tree_browser.setFactoryForManager(manager_map['int'], factory_map['int'])
        box_browser.setFactoryForManager(manager_map['int'], factory_map['int'])
        button_browser.setFactoryForManager(manager_map['int'], factory_map['int'])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # int_read_write
        manager_map['int'].valueChanged.connect(set_value)
        property_ = manager_map['int'].addProperty("int_read_write")
        property_.propertyManager().setReadOnly(property_, False)
        property_.propertyManager().setUnit(property_, "V")

        property_.propertyManager().setMinimum(property_, 0)
        property_.propertyManager().setMaximum(property_, 2)
        property_.propertyManager().setValue(property_, 3)
        tree_browser.setFactoryForManager(manager_map['int'], factory_map['int'])
        box_browser.setFactoryForManager(manager_map['int'], factory_map['int'])
        button_browser.setFactoryForManager(manager_map['int'], factory_map['int'])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # int_read_write spinbox
        manager_map['int2'].valueChanged.connect(set_value)
        property_ = manager_map['int2'].addProperty("int_spinbox")
        property_.propertyManager().setReadOnly(property_, False)
        property_.propertyManager().setUnit(property_, "V")

        property_.propertyManager().setMinimum(property_, 0)
        property_.propertyManager().setMaximum(property_, 2)
        property_.propertyManager().setValue(property_, 3)
        tree_browser.setFactoryForManager(manager_map['int2'], factory_map['int2'])
        box_browser.setFactoryForManager(manager_map['int2'], factory_map['int2'])
        button_browser.setFactoryForManager(manager_map['int2'], factory_map['int2'])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # int_read_write slider
        manager_map['int3'].valueChanged.connect(set_value)
        property_ = manager_map['int3'].addProperty("int_slider")
        property_.propertyManager().setReadOnly(property_, False)
        property_.propertyManager().setUnit(property_, "V")

        property_.propertyManager().setMinimum(property_, 0)
        property_.propertyManager().setMaximum(property_, 2)
        property_.propertyManager().setValue(property_, 3)
        tree_browser.setFactoryForManager(manager_map['int3'], factory_map['int3'])
        box_browser.setFactoryForManager(manager_map['int3'], factory_map['int3'])
        button_browser.setFactoryForManager(manager_map['int3'], factory_map['int3'])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # int_read_write scroll
        manager_map['int4'].valueChanged.connect(set_value)
        property_ = manager_map['int4'].addProperty("int_scroll")
        property_.propertyManager().setReadOnly(property_, False)
        property_.propertyManager().setUnit(property_, "V")

        property_.propertyManager().setMinimum(property_, 0)
        property_.propertyManager().setMaximum(property_, 2)
        property_.propertyManager().setValue(property_, 3)
        tree_browser.setFactoryForManager(manager_map['int4'], factory_map['int4'])
        box_browser.setFactoryForManager(manager_map['int4'], factory_map['int4'])
        button_browser.setFactoryForManager(manager_map['int4'], factory_map['int4'])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # float_read
        manager_map['float'].valueChanged.connect(set_value)
        property_ = manager_map['float'].addProperty("float_read")
        property_.propertyManager().setReadOnly(property_, True)
        property_.propertyManager().setScale(property_, Scale.K)
        property_.propertyManager().setUnit(property_, "V")
        property_.propertyManager().setPrecision(property_, 2)
        property_.propertyManager().setMinimum(property_, 0)
        property_.propertyManager().setMaximum(property_, 2)
        property_.propertyManager().setValue(property_, 3.14)
        tree_browser.setFactoryForManager(manager_map['float'], factory_map['float'])
        box_browser.setFactoryForManager(manager_map['float'], factory_map['float'])
        button_browser.setFactoryForManager(manager_map['float'], factory_map['float'])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # float_read_write
        manager_map['float'].valueChanged.connect(set_value)
        property_ = manager_map['float'].addProperty("float_read_write")
        property_.propertyManager().setReadOnly(property_, False)
        property_.propertyManager().setUnit(property_, "V")
        property_.propertyManager().setPrecision(property_, 2)
        property_.propertyManager().setMinimum(property_, 0)
        property_.propertyManager().setMaximum(property_, 2)
        property_.propertyManager().setValue(property_, 3.14)
        tree_browser.setFactoryForManager(manager_map['float'], factory_map['float'])
        box_browser.setFactoryForManager(manager_map['float'], factory_map['float'])
        button_browser.setFactoryForManager(manager_map['float'], factory_map['float'])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # complex
        # manager_map['complex'].valueChanged.connect(set_value)
        #property_ = manager_map['complex'].addProperty("complex")
        #manager_map['complex'].setPkAvg(property_, PkAvg.PK)
        #manager_map['complex'].setFormat(property_, Format.LIN_DEG)
        #property_.propertyManager().setValue(property_, 3.14 - 1j*3.14)
        #tree_browser.setFactoryForManager(manager_map['complex'], factory_map['complex'])
        #box_browser.setFactoryForManager(manager_map['complex'], factory_map['complex'])
        #button_browser.setFactoryForManager(manager_map['complex'], factory_map['complex'])
        #browser_item = tree_browser.addProperty(property_)
        #tree_browser.setExpanded(browser_item, False)
        #browser_item = box_browser.addProperty(property_)
        #browser_item = button_browser.addProperty(property_)
        #button_browser.setExpanded(browser_item, False)

        # array
        #value = np.asarray([1, 2, 3], dtype=np.float)
        # manager_map['array'].valueChanged.connect(set_value)
        #property_ = manager_map['array'].addProperty("array")
        #manager_map["array"].setValue(property_, np.complex_(value).reshape(value.size))
        #tree_browser.setFactoryForManager(manager_map['array'].subComplexPropertyManager(), factory_map['complex'])
        #tree_browser.setFactoryForManager(manager_map['array'], factory_map['array'])
        #box_browser.setFactoryForManager(manager_map['array'].subComplexPropertyManager(), factory_map['complex'])
        #box_browser.setFactoryForManager(manager_map['array'], factory_map['array'])
        #button_browser.setFactoryForManager(manager_map['array'].subComplexPropertyManager(), factory_map['complex'])
        #button_browser.setFactoryForManager(manager_map['array'], factory_map['array'])
        #browser_item = tree_browser.addProperty(property_)
        #tree_browser.setExpanded(browser_item, False)
        #browser_item = box_browser.addProperty(property_)
        #browser_item = button_browser.addProperty(property_)
        #button_browser.setExpanded(browser_item, False)

        # enum
        value = Color.RED
        manager_map['enum'].valueChanged.connect(set_value)
        property_ = manager_map['enum'].addProperty("enum")
        items = sorted(value.__class__.__members__.items(), key=lambda t: t[1].value)
        names = [k for k, v in items]
        manager_map['enum'].setEnumNames(property_, names)
        try:
            manager_map["flag"].setValue(property_, value.value)
        except AttributeError:
            manager_map["flag"].setValue(property_, value)
        tree_browser.setFactoryForManager(manager_map['enum'], factory_map['enum'])
        box_browser.setFactoryForManager(manager_map['enum'], factory_map['enum'])
        button_browser.setFactoryForManager(manager_map['enum'], factory_map['enum'])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # flags
        value = ColorCombiner.PURPLE
        manager_map['flag'].valueChanged.connect(set_value)
        property_ = manager_map['flag'].addProperty("flag")
        items = value.__class__.__members__.items()
        names = [k for ind, (k, v) in enumerate(items) if (v.value & (v.value - 1)) == 0 and v.value != 0]
        manager_map['flag'].setFlagNames(property_, names)
        try:
            manager_map["flag"].setValue(property_, value.value)
        except AttributeError:
            manager_map["flag"].setValue(property_, value)
        tree_browser.setFactoryForManager(manager_map['flag'].subBoolPropertyManager(), factory_map['bool'])
        box_browser.setFactoryForManager(manager_map['flag'].subBoolPropertyManager(), factory_map['bool'])
        button_browser.setFactoryForManager(manager_map['flag'].subBoolPropertyManager(), factory_map['bool'])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # str
        manager_map['str'].valueChanged.connect(set_value)
        property_ = manager_map['str'].addProperty("str")
        property_.propertyManager().setValue(property_, "Hello World")
        tree_browser.setFactoryForManager(manager_map['str'], factory_map['str'])
        box_browser.setFactoryForManager(manager_map['str'], factory_map['str'])
        button_browser.setFactoryForManager(manager_map['str'], factory_map['str'])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # file
        # manager_map['int'].valueChanged.connect(set_value)
        #value = open("temp.txt", mode="w")
        #property_ = manager_map['file'].addProperty("file")
        #manager_map["file"].setValue(property_, value.name)
        #tree_browser.setFactoryForManager(manager_map['file'], factory_map['file'])
        #browser_item = tree_browser.addProperty(property_)
        #tree_browser.setExpanded(browser_item, False)
        #browser_item = box_browser.addProperty(property_)
        #box_browser.setExpanded(browser_item, False)
        #browser_item = button_browser.addProperty(property_)
        #button_browser.setExpanded(browser_item, False)

        # date
        manager_map['date'].valueChanged.connect(set_value)
        property_ = manager_map['date'].addProperty("date")
        property_.propertyManager().setValue(property_, QDate.currentDate())
        tree_browser.setFactoryForManager(manager_map['date'], factory_map['date'])
        box_browser.setFactoryForManager(manager_map['date'], factory_map['date'])
        button_browser.setFactoryForManager(manager_map['date'], factory_map['date'])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # datetime
        manager_map['datetime'].valueChanged.connect(set_value)
        property_ = manager_map['datetime'].addProperty("datetime")
        property_.propertyManager().setValue(property_, QDateTime.currentDateTime())
        tree_browser.setFactoryForManager(manager_map['datetime'], factory_map['datetime'])
        box_browser.setFactoryForManager(manager_map['datetime'], factory_map['datetime'])
        button_browser.setFactoryForManager(manager_map['datetime'], factory_map['datetime'])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # time
        manager_map['time'].valueChanged.connect(set_value)
        property_ = manager_map['time'].addProperty("time")
        property_.propertyManager().setValue(property_, QTime.currentTime())
        tree_browser.setFactoryForManager(manager_map['time'], factory_map['time'])
        box_browser.setFactoryForManager(manager_map['time'], factory_map['time'])
        button_browser.setFactoryForManager(manager_map['time'], factory_map['time'])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)
    
        # locale
        manager_map['locale'].valueChanged.connect(set_value)
        property_ = manager_map['locale'].addProperty("locale")
        property_.propertyManager().setValue(property_, QLocale(QLocale.English, QLocale.Canada))
        tree_browser.setFactoryForManager(manager_map['locale'].subEnumPropertyManager(), factory_map['enum'])
        box_browser.setFactoryForManager(manager_map['locale'].subEnumPropertyManager(), factory_map['enum'])
        button_browser.setFactoryForManager(manager_map['locale'].subEnumPropertyManager(), factory_map['enum'])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # point
        manager_map['point'].valueChanged.connect(set_value)
        property_ = manager_map['point'].addProperty("point")
        property_.propertyManager().setValue(property_, QPoint(1, 3))
        tree_browser.setFactoryForManager(manager_map['point'].subIntPropertyManager(), factory_map['int'])
        box_browser.setFactoryForManager(manager_map['point'].subIntPropertyManager(), factory_map['int'])
        button_browser.setFactoryForManager(manager_map['point'].subIntPropertyManager(), factory_map['int'])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # pointf
        manager_map['pointf'].valueChanged.connect(set_value)
        property_ = manager_map['pointf'].addProperty("pointf")
        property_.propertyManager().setValue(property_, QPointF(1.23, 3.21))
        tree_browser.setFactoryForManager(manager_map['pointf'].subDoublePropertyManager(), factory_map['float'])
        box_browser.setFactoryForManager(manager_map['pointf'].subDoublePropertyManager(), factory_map['float'])
        button_browser.setFactoryForManager(manager_map['pointf'].subDoublePropertyManager(), factory_map['float'])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # size_read
        manager_map['size'].valueChanged.connect(set_value)
        property_ = manager_map['size'].addProperty("size_read")
        property_.propertyManager().setReadOnly(property_, True)
        property_.propertyManager().setMinimum(property_, QSize(0, 0))
        property_.propertyManager().setMaximum(property_, QSize(2, 2))
        property_.propertyManager().setValue(property_, QSize(-1, 3))
        tree_browser.setFactoryForManager(manager_map['size'].subIntPropertyManager(), factory_map['int'])
        box_browser.setFactoryForManager(manager_map['size'].subIntPropertyManager(), factory_map['int'])
        button_browser.setFactoryForManager(manager_map['size'].subIntPropertyManager(), factory_map['int'])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # size_read_write
        manager_map['size'].valueChanged.connect(set_value)
        property_ = manager_map['size'].addProperty("size_read")
        property_.propertyManager().setReadOnly(property_, False)
        property_.propertyManager().setMinimum(property_, QSize(0, 0))
        property_.propertyManager().setMaximum(property_, QSize(255, 255))
        property_.propertyManager().setValue(property_, QSize(-1, 3))
        tree_browser.setFactoryForManager(manager_map['size'].subIntPropertyManager(), factory_map['int'])
        box_browser.setFactoryForManager(manager_map['size'].subIntPropertyManager(), factory_map['int'])
        button_browser.setFactoryForManager(manager_map['size'].subIntPropertyManager(), factory_map['int'])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # sizef_read
        manager_map['sizef'].valueChanged.connect(set_value)
        property_ = manager_map['sizef'].addProperty("sizef")
        property_.propertyManager().setReadOnly(property_, True)
        property_.propertyManager().setMinimum(property_, QSize(0, 0))
        property_.propertyManager().setMaximum(property_, QSize(2, 2))
        property_.propertyManager().setValue(property_, QSizeF(-1.23, 3.21))
        tree_browser.setFactoryForManager(manager_map['sizef'].subDoublePropertyManager(), factory_map['float'])
        box_browser.setFactoryForManager(manager_map['sizef'].subDoublePropertyManager(), factory_map['float'])
        button_browser.setFactoryForManager(manager_map['sizef'].subDoublePropertyManager(), factory_map['float'])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # sizef_read_write
        manager_map['sizef'].valueChanged.connect(set_value)
        property_ = manager_map['sizef'].addProperty("sizef")
        property_.propertyManager().setReadOnly(property_, False)
        property_.propertyManager().setMinimum(property_, QSize(0, 0))
        property_.propertyManager().setMaximum(property_, QSize(2, 2))
        property_.propertyManager().setValue(property_, QSizeF(-1.23, 3.21))
        tree_browser.setFactoryForManager(manager_map['sizef'].subDoublePropertyManager(), factory_map['float'])
        box_browser.setFactoryForManager(manager_map['sizef'].subDoublePropertyManager(), factory_map['float'])
        button_browser.setFactoryForManager(manager_map['sizef'].subDoublePropertyManager(), factory_map['float'])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # rect
        manager_map['rect'].valueChanged.connect(set_value)
        property_ = manager_map['rect'].addProperty("rect")
        property_.propertyManager().setValue(property_, QRect(0, 1, 2, 3))
        tree_browser.setFactoryForManager(manager_map['rect'].subIntPropertyManager(), factory_map['int'])
        box_browser.setFactoryForManager(manager_map['rect'].subIntPropertyManager(), factory_map['int'])
        button_browser.setFactoryForManager(manager_map['rect'].subIntPropertyManager(), factory_map['int'])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # rectf
        manager_map['rectf'].valueChanged.connect(set_value)
        property_ = manager_map['rectf'].addProperty("rectf")
        property_.propertyManager().setValue(property_, QRectF(0.12, 1.23, 2.34, 3.45))
        tree_browser.setFactoryForManager(manager_map['rectf'].subDoublePropertyManager(), factory_map['float'])
        box_browser.setFactoryForManager(manager_map['rectf'].subDoublePropertyManager(), factory_map['float'])
        button_browser.setFactoryForManager(manager_map['rectf'].subDoublePropertyManager(), factory_map['float'])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # cursor
        manager_map['cursor'].valueChanged.connect(set_value)
        property_ = manager_map['cursor'].addProperty("cursor")
        property_.propertyManager().setValue(property_, QCursor())
        tree_browser.setFactoryForManager(manager_map['cursor'], factory_map['cursor'])
        box_browser.setFactoryForManager(manager_map['cursor'], factory_map['cursor'])
        button_browser.setFactoryForManager(manager_map['cursor'], factory_map['cursor'])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # color
        manager_map['color'].valueChanged.connect(set_value)
        property_ = manager_map['color'].addProperty("color")
        property_.propertyManager().setValue(property_, QColor())
        tree_browser.setFactoryForManager(manager_map['color'], factory_map['color'])
        box_browser.setFactoryForManager(manager_map['color'], factory_map['color'])
        button_browser.setFactoryForManager(manager_map['color'], factory_map['color'])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # font
        manager_map['font'].valueChanged.connect(set_value)
        property_ = manager_map['font'].addProperty("font")
        property_.propertyManager().setValue(property_, QFont())
        tree_browser.setFactoryForManager(manager_map['font'], factory_map['font'])
        box_browser.setFactoryForManager(manager_map['font'], factory_map['font'])
        button_browser.setFactoryForManager(manager_map['font'], factory_map['font'])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # size_policy
        manager_map['size_policy'].valueChanged.connect(set_value)
        property_ = manager_map['size_policy'].addProperty("size_policy")
        property_.propertyManager().setValue(property_, QSizePolicy())
        tree_browser.setFactoryForManager(manager_map['size_policy'].subEnumPropertyManager(), factory_map['enum'])
        tree_browser.setFactoryForManager(manager_map['size_policy'].subIntPropertyManager(), factory_map['int'])
        box_browser.setFactoryForManager(manager_map['size_policy'].subEnumPropertyManager(), factory_map['enum'])
        box_browser.setFactoryForManager(manager_map['size_policy'].subIntPropertyManager(), factory_map['int'])
        button_browser.setFactoryForManager(manager_map['size_policy'].subEnumPropertyManager(), factory_map['enum'])
        button_browser.setFactoryForManager(manager_map['size_policy'].subIntPropertyManager(), factory_map['int'])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

    tree_browser.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
    tree_scroll_area.setWidgetResizable(True)
    tree_scroll_area.setWidget(tree_browser)
    layout.addWidget(QLabel("Tree Browser", parent=dialog), 0, 0)
    layout.addWidget(tree_scroll_area, 1, 0)

    tree_scroll_area.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
    box_scroll_area.setWidgetResizable(True)
    box_scroll_area.setWidget(box_browser)
    layout.addWidget(QLabel("Box Browser", parent=dialog), 0, 1)
    layout.addWidget(box_scroll_area, 1, 1)

    button_scroll_area.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
    button_scroll_area.setWidgetResizable(True)
    button_scroll_area.setWidget(button_browser)
    layout.addWidget(QLabel("Button Browser", parent=dialog), 0, 2)
    layout.addWidget(button_scroll_area, 1, 2)

    dialog.setLayout(layout)
    dialog.showMaximized()
    sys.exit(app.exec_())
