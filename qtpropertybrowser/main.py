import sys
from enum import Enum, Flag, auto, unique

import numpy as np
from PySide2.QtCore import Qt, QDate, QDateTime, QTime, QLocale, QPoint, QPointF, QSize, QSizeF, QRect, QRectF
from PySide2.QtGui import QCursor, QColor, QFont, QKeySequence
from PySide2.QtWidgets import QSizePolicy
from PySide2.QtWidgets import QApplication, QDialog, QLabel, QGridLayout, QScrollArea

from qtpropertybrowser import QtTreePropertyBrowser, QtGroupBoxPropertyBrowser, QtButtonPropertyBrowser
from qtpropertybrowser import QtIntPropertyManager, QtBoolPropertyManager
from qtpropertybrowser import QtDoublePropertyManager, QtComplexPropertyManager, QtComplexArrayPropertyManager
from qtpropertybrowser import QtStringPropertyManager, QtFilePropertyManager
from qtpropertybrowser import QtDatePropertyManager, QtTimePropertyManager, QtDateTimePropertyManager
from qtpropertybrowser import QtCharPropertyManager, QtKeySequencePropertyManager
from qtpropertybrowser import QtLocalePropertyManager
from qtpropertybrowser import QtPointPropertyManager, QtPointFPropertyManager
from qtpropertybrowser import QtSizePropertyManager, QtSizeFPropertyManager
from qtpropertybrowser import QtRectPropertyManager, QtRectFPropertyManager
from qtpropertybrowser import QtEnumPropertyManager, QtFlagPropertyManager
from qtpropertybrowser import QtSizePolicyPropertyManager
from qtpropertybrowser import QtFontPropertyManager, QtColorPropertyManager, QtCursorPropertyManager
from qtpropertybrowser import QtIntEditFactory, QtSpinBoxFactory, QtSliderFactory, QtScrollBarFactory, QtCheckBoxFactory
from qtpropertybrowser import QtDoubleEditFactory, QtDoubleSpinBoxFactory, QtComplexEditFactory, QtArrayEditFactory
from qtpropertybrowser import QtLineEditFactory, QtFileEditorFactory
from qtpropertybrowser import QtDateEditFactory, QtTimeEditFactory, QtDateTimeEditFactory
from qtpropertybrowser import QtKeySequenceEditorFactory, QtCharEditorFactory
from qtpropertybrowser import QtEnumEditorFactory
from qtpropertybrowser import QtFontEditorFactory, QtColorEditorFactory, QtCursorEditorFactory
from qtpropertybrowser import PkAvg, Scale, Format, Domain, Attribute


@unique
class Manager(Enum):
    INT_SPIN = auto()
    INT_EDIT = auto()
    INT_SLIDER = auto()
    INT_SCROLL = auto()
    BOOL = auto()
    DOUBLE_SPIN = auto()
    DOUBLE_EDIT = auto()
    COMPLEX_EDIT = auto()
    COMPLEX_VECTOR = auto()
    STRING = auto()
    FILE = auto()
    DATE = auto()
    TIME = auto()
    DATETIME = auto()
    KEY_SEQUENCE = auto()
    CHAR = auto()
    LOCALE = auto()
    POINT = auto()
    POINTF = auto()
    SIZE = auto()
    SIZEF = auto()
    RECT = auto()
    RECTF = auto()
    ENUM = auto()
    FLAG = auto()
    SIZE_POLICY = auto()
    FONT = auto()
    COLOR = auto()
    CURSOR = auto()

@unique
class Factory(Enum):
    INT_SPIN = auto()
    INT_EDIT = auto()
    INT_SLIDER = auto()
    INT_SCROLL = auto()
    BOOL = auto()
    DOUBLE_SPIN = auto()
    DOUBLE_EDIT = auto()
    COMPLEX_EDIT = auto()
    COMPLEX_VECTOR = auto()
    STRING = auto()
    FILE = auto()
    DATE = auto()
    TIME = auto()
    DATETIME = auto()
    KEY_SEQUENCE = auto()
    CHAR = auto()
    LOCALE = auto()
    POINT = auto()
    POINTF = auto()
    SIZE = auto()
    SIZEF = auto()
    RECT = auto()
    RECTF = auto()
    ENUM = auto()
    FLAG = auto()
    SIZE_POLICY = auto()
    FONT = auto()
    COLOR = auto()
    CURSOR = auto()


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
        tree_browser.setAttributes([Attribute.MINIMUM, Attribute.MAXIMUM, Attribute.CHECK])
        # tree_browser.setAttributes([Attribute.PKAVG, Attribute.UNIT, Attribute.FORMAT, Attribute.CHECK])
        box_scroll_area = QScrollArea()
        box_browser = QtGroupBoxPropertyBrowser()
        box_browser.setAttributes([Attribute.MINIMUM, Attribute.MAXIMUM, Attribute.CHECK])
        # box_browser.setAttributes([Attribute.PKAVG, Attribute.UNIT, Attribute.FORMAT, Attribute.CHECK])
        button_scroll_area = QScrollArea()
        button_browser = QtButtonPropertyBrowser()
        button_browser.setAttributes([Attribute.MINIMUM, Attribute.MAXIMUM, Attribute.CHECK])
        # button_browser.setAttributes([Attribute.PKAVG, Attribute.UNIT, Attribute.FORMAT, Attribute.CHECK])

        manager_map = {Manager.INT_SPIN: QtIntPropertyManager(),  # todo: Does not support Attribute.PKAVG, Attribute.UNIT, Attribute.FORMAT
                       Manager.INT_EDIT: QtIntPropertyManager(),
                       Manager.INT_SLIDER: QtIntPropertyManager(),
                       Manager.INT_SCROLL: QtIntPropertyManager(),
                       Manager.BOOL: QtBoolPropertyManager(),
                       Manager.DOUBLE_SPIN: QtDoublePropertyManager(), # todo: Does not support Attribute.PKAVG, Attribute.UNIT, Attribute.FORMAT
                       Manager.DOUBLE_EDIT: QtDoublePropertyManager(),
                       Manager.COMPLEX_EDIT: QtComplexPropertyManager(),
                       Manager.COMPLEX_VECTOR: QtComplexArrayPropertyManager(),
                       Manager.STRING: QtStringPropertyManager(),
                       Manager.FILE: QtFilePropertyManager(),
                       Manager.DATE: QtDatePropertyManager(),
                       Manager.TIME: QtTimePropertyManager(),
                       Manager.DATETIME: QtDateTimePropertyManager(),
                       Manager.KEY_SEQUENCE: QtKeySequencePropertyManager(),
                       Manager.CHAR: QtCharPropertyManager(),
                       Manager.LOCALE: QtLocalePropertyManager(),
                       Manager.POINT: QtPointPropertyManager(),
                       Manager.POINTF: QtPointFPropertyManager(),
                       Manager.SIZE: QtSizePropertyManager(),
                       Manager.SIZEF: QtSizeFPropertyManager(),
                       Manager.RECT: QtRectPropertyManager(),
                       Manager.RECTF: QtRectFPropertyManager(),
                       Manager.ENUM: QtEnumPropertyManager(),
                       Manager.FLAG: QtFlagPropertyManager(),
                       Manager.SIZE_POLICY: QtSizePolicyPropertyManager(),
                       Manager.FONT: QtFontPropertyManager(),
                       Manager.COLOR: QtColorPropertyManager(),
                       Manager.CURSOR: QtCursorPropertyManager(),
                       }
        factory_map = {Factory.INT_SPIN: QtSpinBoxFactory(),
                       Factory.INT_EDIT: QtIntEditFactory(),
                       Factory.INT_SLIDER: QtSliderFactory(),
                       Factory.INT_SCROLL: QtScrollBarFactory(),
                       Factory.BOOL: QtCheckBoxFactory(),
                       Factory.DOUBLE_SPIN: QtDoubleSpinBoxFactory(),
                       Factory.DOUBLE_EDIT: QtDoubleEditFactory(),
                       Factory.COMPLEX_EDIT: QtComplexEditFactory(),
                       Factory.COMPLEX_VECTOR: QtArrayEditFactory(),
                       Factory.STRING: QtLineEditFactory(),
                       Factory.FILE: QtFileEditorFactory(),
                       Factory.DATE: QtDateEditFactory(),
                       Factory.TIME: QtTimeEditFactory(),
                       Factory.DATETIME: QtDateTimeEditFactory(),
                       Factory.KEY_SEQUENCE: QtKeySequenceEditorFactory(),
                       Factory.CHAR: QtCharEditorFactory(),
                       Factory.LOCALE: None,
                       Factory.POINT: None,
                       Factory.POINTF: None,
                       Factory.SIZE: None,
                       Factory.SIZEF: None,
                       Factory.RECT: None,
                       Factory.RECTF: None,
                       Factory.ENUM: QtEnumEditorFactory(),
                       Factory.FLAG: None,
                       Factory.SIZE_POLICY: None,
                       Factory.FONT: QtFontEditorFactory(),
                       Factory.COLOR: QtColorEditorFactory(),
                       Factory.CURSOR: QtCursorEditorFactory(),
                       }

        factory_map[Factory.COMPLEX_VECTOR].setSubFactory(factory_map[Factory.COMPLEX_EDIT])
        print(factory_map[Factory.COMPLEX_EDIT])
        print(factory_map[Factory.COMPLEX_VECTOR].subFactory())

        # int_spin_rw
        manager_map[Manager.INT_SPIN].valueChanged.connect(set_value)
        property_ = manager_map[Manager.INT_SPIN].addProperty("int_spinbox_rw")
        property_.propertyManager().setReadOnly(property_, False)
        property_.propertyManager().setUnit(property_, "V")
        property_.propertyManager().setMinimum(property_, 0)
        property_.propertyManager().setMaximum(property_, 2)
        property_.propertyManager().setValue(property_, 3)
        tree_browser.setFactoryForManager(manager_map[Manager.INT_SPIN], factory_map[Factory.INT_SPIN])
        box_browser.setFactoryForManager(manager_map[Manager.INT_SPIN], factory_map[Factory.INT_SPIN])
        button_browser.setFactoryForManager(manager_map[Manager.INT_SPIN], factory_map[Factory.INT_SPIN])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # int_edit_r
        manager_map[Manager.INT_EDIT].valueChanged.connect(set_value)
        property_ = manager_map[Manager.INT_EDIT].addProperty("int_edit_r")
        property_.propertyManager().setReadOnly(property_, True)
        property_.propertyManager().setUnit(property_, "V")
        property_.propertyManager().setMinimum(property_, 0)
        property_.propertyManager().setMaximum(property_, 2)
        property_.propertyManager().setValue(property_, 3)
        tree_browser.setFactoryForManager(manager_map[Manager.INT_EDIT], factory_map[Factory.INT_EDIT])
        box_browser.setFactoryForManager(manager_map[Manager.INT_EDIT], factory_map[Factory.INT_EDIT])
        button_browser.setFactoryForManager(manager_map[Manager.INT_EDIT], factory_map[Factory.INT_EDIT])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # int_edit_rw
        manager_map[Manager.INT_EDIT].valueChanged.connect(set_value)
        property_ = manager_map[Manager.INT_EDIT].addProperty("int_edit_rw")
        property_.propertyManager().setReadOnly(property_, False)
        property_.propertyManager().setUnit(property_, "V")
        property_.propertyManager().setMinimum(property_, 0)
        property_.propertyManager().setMaximum(property_, 2)
        property_.propertyManager().setValue(property_, 3)
        tree_browser.setFactoryForManager(manager_map[Manager.INT_EDIT], factory_map[Factory.INT_EDIT])
        box_browser.setFactoryForManager(manager_map[Manager.INT_EDIT], factory_map[Factory.INT_EDIT])
        button_browser.setFactoryForManager(manager_map[Manager.INT_EDIT], factory_map[Factory.INT_EDIT])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # int_slider_rw
        manager_map[Manager.INT_SLIDER].valueChanged.connect(set_value)
        property_ = manager_map[Manager.INT_SLIDER].addProperty("int_slider_rw")
        property_.propertyManager().setReadOnly(property_, False)
        property_.propertyManager().setUnit(property_, "V")

        property_.propertyManager().setMinimum(property_, 0)
        property_.propertyManager().setMaximum(property_, 2)
        property_.propertyManager().setValue(property_, 3)
        tree_browser.setFactoryForManager(manager_map[Manager.INT_SLIDER], factory_map[Factory.INT_SLIDER])
        box_browser.setFactoryForManager(manager_map[Manager.INT_SLIDER], factory_map[Factory.INT_SLIDER])
        button_browser.setFactoryForManager(manager_map[Manager.INT_SLIDER], factory_map[Factory.INT_SLIDER])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # int_scroll_rw
        manager_map[Manager.INT_SCROLL].valueChanged.connect(set_value)
        property_ = manager_map[Manager.INT_SCROLL].addProperty("int_scroll_rw")
        property_.propertyManager().setReadOnly(property_, False)
        property_.propertyManager().setUnit(property_, "V")
        property_.propertyManager().setMinimum(property_, 0)
        property_.propertyManager().setMaximum(property_, 2)
        property_.propertyManager().setValue(property_, 3)
        tree_browser.setFactoryForManager(manager_map[Manager.INT_SCROLL], factory_map[Factory.INT_SCROLL])
        box_browser.setFactoryForManager(manager_map[Manager.INT_SCROLL], factory_map[Factory.INT_SCROLL])
        button_browser.setFactoryForManager(manager_map[Manager.INT_SCROLL], factory_map[Factory.INT_SCROLL])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # bool
        manager_map[Manager.BOOL].valueChanged.connect(set_value)
        property_ = manager_map[Manager.BOOL].addProperty("bool")
        property_.propertyManager().setValue(property_, False)
        tree_browser.setFactoryForManager(manager_map[Manager.BOOL], factory_map[Factory.BOOL])
        box_browser.setFactoryForManager(manager_map[Manager.BOOL], factory_map[Factory.BOOL])
        button_browser.setFactoryForManager(manager_map[Manager.BOOL], factory_map[Factory.BOOL])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # double_spin_rw
        manager_map[Manager.DOUBLE_SPIN].valueChanged.connect(set_value)
        property_ = manager_map[Manager.DOUBLE_SPIN].addProperty("double_spin_rw")
        property_.propertyManager().setReadOnly(property_, False)
        property_.propertyManager().setUnit(property_, "V")
        property_.propertyManager().setPrecision(property_, 2)
        property_.propertyManager().setMinimum(property_, 0)
        property_.propertyManager().setMaximum(property_, 2)
        property_.propertyManager().setValue(property_, 3.14)
        tree_browser.setFactoryForManager(manager_map[Manager.DOUBLE_SPIN], factory_map[Factory.DOUBLE_SPIN])
        box_browser.setFactoryForManager(manager_map[Manager.DOUBLE_SPIN], factory_map[Factory.DOUBLE_SPIN])
        button_browser.setFactoryForManager(manager_map[Manager.DOUBLE_SPIN], factory_map[Factory.DOUBLE_SPIN])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # double_edit_r
        manager_map[Manager.DOUBLE_EDIT].valueChanged.connect(set_value)
        property_ = manager_map[Manager.DOUBLE_EDIT].addProperty("double_edit_r")
        property_.propertyManager().setReadOnly(property_, True)
        property_.propertyManager().setScale(property_, Scale.K)
        property_.propertyManager().setUnit(property_, "V")
        property_.propertyManager().setPrecision(property_, 2)
        property_.propertyManager().setMinimum(property_, 0)
        property_.propertyManager().setMaximum(property_, 2)
        property_.propertyManager().setValue(property_, 3.14)
        tree_browser.setFactoryForManager(manager_map[Manager.DOUBLE_EDIT], factory_map[Factory.DOUBLE_EDIT])
        box_browser.setFactoryForManager(manager_map[Manager.DOUBLE_EDIT], factory_map[Factory.DOUBLE_EDIT])
        button_browser.setFactoryForManager(manager_map[Manager.DOUBLE_EDIT], factory_map[Factory.DOUBLE_EDIT])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # double_edit_rw
        manager_map[Manager.DOUBLE_EDIT].valueChanged.connect(set_value)
        property_ = manager_map[Manager.DOUBLE_EDIT].addProperty("double_edit_rw")
        property_.propertyManager().setReadOnly(property_, False)
        property_.propertyManager().setUnit(property_, "V")
        property_.propertyManager().setPrecision(property_, 2)
        property_.propertyManager().setMinimum(property_, 0)
        property_.propertyManager().setMaximum(property_, 2)
        property_.propertyManager().setValue(property_, 3.14)
        tree_browser.setFactoryForManager(manager_map[Manager.DOUBLE_EDIT], factory_map[Factory.DOUBLE_EDIT])
        box_browser.setFactoryForManager(manager_map[Manager.DOUBLE_EDIT], factory_map[Factory.DOUBLE_EDIT])
        button_browser.setFactoryForManager(manager_map[Manager.DOUBLE_EDIT], factory_map[Factory.DOUBLE_EDIT])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # complex_edit_r
        manager_map[Manager.COMPLEX_EDIT].valueChanged.connect(set_value)
        property_ = manager_map[Manager.COMPLEX_EDIT].addProperty("complex_edit_r")
        property_.propertyManager().setReadOnly(property_, True)
        property_.propertyManager().setUnit(property_, "V")
        property_.propertyManager().setPrecision(property_, 2)
        property_.propertyManager().setMinimum(property_, 0)
        property_.propertyManager().setMaximum(property_, 2)
        property_.propertyManager().setValue(property_, 2 + 2j)
        tree_browser.setFactoryForManager(manager_map[Manager.COMPLEX_EDIT], factory_map[Factory.COMPLEX_EDIT])
        box_browser.setFactoryForManager(manager_map[Manager.COMPLEX_EDIT], factory_map[Factory.COMPLEX_EDIT])
        button_browser.setFactoryForManager(manager_map[Manager.COMPLEX_EDIT], factory_map[Factory.COMPLEX_EDIT])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # complex_edit_rw
        manager_map[Manager.COMPLEX_EDIT].valueChanged.connect(set_value)
        property_ = manager_map[Manager.COMPLEX_EDIT].addProperty("complex_edit_rw")
        property_.propertyManager().setReadOnly(property_, False)
        property_.propertyManager().setScale(property_, Scale.K)
        property_.propertyManager().setUnit(property_, "V")
        property_.propertyManager().setPrecision(property_, 2)
        property_.propertyManager().setMinimum(property_, 0)
        property_.propertyManager().setMaximum(property_, 2)
        property_.propertyManager().setValue(property_, 2 + 2j)
        tree_browser.setFactoryForManager(manager_map[Manager.COMPLEX_EDIT], factory_map[Factory.COMPLEX_EDIT])
        box_browser.setFactoryForManager(manager_map[Manager.COMPLEX_EDIT], factory_map[Factory.COMPLEX_EDIT])
        button_browser.setFactoryForManager(manager_map[Manager.COMPLEX_EDIT], factory_map[Factory.COMPLEX_EDIT])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # complex_vector_r
        manager_map[Manager.COMPLEX_VECTOR].valueChanged.connect(set_value)
        property_ = manager_map[Manager.COMPLEX_VECTOR].addProperty("complex_vector_r")
        property_.propertyManager().setReadOnly(property_, True)
        property_.propertyManager().setUnit(property_, "V")
        property_.propertyManager().setPrecision(property_, 2)
        property_.propertyManager().setMinimum(property_, [0, 0])
        property_.propertyManager().setMaximum(property_, [2, 2])
        property_.propertyManager().setValue(property_, [2 + 2j, 2 + 2j])
        tree_browser.setFactoryForManager(manager_map[Manager.COMPLEX_VECTOR], factory_map[Factory.COMPLEX_VECTOR])
        box_browser.setFactoryForManager(manager_map[Manager.COMPLEX_VECTOR], factory_map[Factory.COMPLEX_VECTOR])
        button_browser.setFactoryForManager(manager_map[Manager.COMPLEX_VECTOR], factory_map[Factory.COMPLEX_VECTOR])
        tree_browser.setFactoryForManager(manager_map[Manager.COMPLEX_VECTOR].subComplexPropertyManager(),
                                          factory_map[Factory.COMPLEX_EDIT])
        box_browser.setFactoryForManager(manager_map[Manager.COMPLEX_VECTOR].subComplexPropertyManager(),
                                         factory_map[Factory.COMPLEX_EDIT])
        button_browser.setFactoryForManager(manager_map[Manager.COMPLEX_VECTOR].subComplexPropertyManager(),
                                            factory_map[Factory.COMPLEX_EDIT])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # complex_vector_rw
        manager_map[Manager.COMPLEX_VECTOR].valueChanged.connect(set_value)
        property_ = manager_map[Manager.COMPLEX_VECTOR].addProperty("complex_vector_rw2")
        property_.propertyManager().setReadOnly(property_, False)
        property_.propertyManager().setUnit(property_, "V")
        property_.propertyManager().setPrecision(property_, 2)
        property_.propertyManager().setMinimum(property_, [0, 0, 0, 0, 0])
        property_.propertyManager().setMaximum(property_, [2, 2, 2, 2, 2])
        property_.propertyManager().setValue(property_, [2 + 2j, 2 + 2j, 2 + 2j, 2 + 2j, 2 + 2j])
        tree_browser.setFactoryForManager(manager_map[Manager.COMPLEX_VECTOR], factory_map[Factory.COMPLEX_VECTOR])
        box_browser.setFactoryForManager(manager_map[Manager.COMPLEX_VECTOR], factory_map[Factory.COMPLEX_VECTOR])
        button_browser.setFactoryForManager(manager_map[Manager.COMPLEX_VECTOR], factory_map[Factory.COMPLEX_VECTOR])
        tree_browser.setFactoryForManager(manager_map[Manager.COMPLEX_VECTOR].subComplexPropertyManager(),
                                          factory_map[Factory.COMPLEX_EDIT])
        box_browser.setFactoryForManager(manager_map[Manager.COMPLEX_VECTOR].subComplexPropertyManager(),
                                         factory_map[Factory.COMPLEX_EDIT])
        button_browser.setFactoryForManager(manager_map[Manager.COMPLEX_VECTOR].subComplexPropertyManager(),
                                            factory_map[Factory.COMPLEX_EDIT])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # str
        manager_map[Manager.STRING].valueChanged.connect(set_value)
        property_ = manager_map[Manager.STRING].addProperty("str")
        property_.propertyManager().setValue(property_, "Hello World")
        tree_browser.setFactoryForManager(manager_map[Manager.STRING], factory_map[Factory.STRING])
        box_browser.setFactoryForManager(manager_map[Manager.STRING], factory_map[Factory.STRING])
        button_browser.setFactoryForManager(manager_map[Manager.STRING], factory_map[Factory.STRING])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # file
        value = open("./file.txt", mode='w')
        value.close()
        manager_map[Manager.FILE].valueChanged.connect(set_value)
        property_ = manager_map[Manager.FILE].addProperty("file")
        property_.propertyManager().setReadOnly(property_, False)
        property_.setEnabled(True)
        property_.propertyManager().setValue(property_, value.name)
        tree_browser.setFactoryForManager(manager_map[Manager.FILE], factory_map[Factory.FILE])
        box_browser.setFactoryForManager(manager_map[Manager.FILE], factory_map[Factory.FILE])
        button_browser.setFactoryForManager(manager_map[Manager.FILE], factory_map[Factory.FILE])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # date
        manager_map[Manager.DATE].valueChanged.connect(set_value)
        property_ = manager_map[Manager.DATE].addProperty("date")
        property_.propertyManager().setValue(property_, QDate.currentDate())
        tree_browser.setFactoryForManager(manager_map[Manager.DATE], factory_map[Factory.DATE])
        box_browser.setFactoryForManager(manager_map[Manager.DATE], factory_map[Factory.DATE])
        button_browser.setFactoryForManager(manager_map[Manager.DATE], factory_map[Factory.DATE])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # time
        manager_map[Manager.TIME].valueChanged.connect(set_value)
        property_ = manager_map[Manager.TIME].addProperty("time")
        property_.propertyManager().setValue(property_, QTime.currentTime())
        tree_browser.setFactoryForManager(manager_map[Manager.TIME], factory_map[Factory.TIME])
        box_browser.setFactoryForManager(manager_map[Manager.TIME], factory_map[Factory.TIME])
        button_browser.setFactoryForManager(manager_map[Manager.TIME], factory_map[Factory.TIME])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # datetime
        manager_map[Manager.DATETIME].valueChanged.connect(set_value)
        property_ = manager_map[Manager.DATETIME].addProperty("datetime")
        property_.propertyManager().setValue(property_, QDateTime.currentDateTime())
        tree_browser.setFactoryForManager(manager_map[Manager.DATETIME], factory_map[Factory.DATETIME])
        box_browser.setFactoryForManager(manager_map[Manager.DATETIME], factory_map[Factory.DATETIME])
        button_browser.setFactoryForManager(manager_map[Manager.DATETIME], factory_map[Factory.DATETIME])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # key sequence
        value = QKeySequence(Qt.CTRL + Qt.Key_P)
        manager_map[Manager.KEY_SEQUENCE].valueChanged.connect(set_value)
        property_ = manager_map[Manager.KEY_SEQUENCE].addProperty("key sequence")
        property_.propertyManager().setValue(property_, value)
        tree_browser.setFactoryForManager(manager_map[Manager.KEY_SEQUENCE], factory_map[Factory.KEY_SEQUENCE])
        box_browser.setFactoryForManager(manager_map[Manager.KEY_SEQUENCE], factory_map[Factory.KEY_SEQUENCE])
        button_browser.setFactoryForManager(manager_map[Manager.KEY_SEQUENCE], factory_map[Factory.KEY_SEQUENCE])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # char
        value = 'a'
        manager_map[Manager.CHAR].valueChanged.connect(set_value)
        property_ = manager_map[Manager.CHAR].addProperty("char")
        property_.propertyManager().setValue(property_, value)
        tree_browser.setFactoryForManager(manager_map[Manager.CHAR], factory_map[Factory.CHAR])
        box_browser.setFactoryForManager(manager_map[Manager.CHAR], factory_map[Factory.CHAR])
        button_browser.setFactoryForManager(manager_map[Manager.CHAR], factory_map[Factory.CHAR])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # locale
        manager_map[Manager.LOCALE].valueChanged.connect(set_value)
        property_ = manager_map[Manager.LOCALE].addProperty("locale")
        property_.propertyManager().setValue(property_, QLocale(QLocale.English, QLocale.Canada))
        tree_browser.setFactoryForManager(manager_map[Manager.LOCALE].subEnumPropertyManager(),
                                          factory_map[Factory.ENUM])
        box_browser.setFactoryForManager(manager_map[Manager.LOCALE].subEnumPropertyManager(),
                                         factory_map[Factory.ENUM])
        button_browser.setFactoryForManager(manager_map[Manager.LOCALE].subEnumPropertyManager(),
                                            factory_map[Factory.ENUM])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # point
        manager_map[Manager.POINT].valueChanged.connect(set_value)
        property_ = manager_map[Manager.POINT].addProperty("point")
        property_.propertyManager().setValue(property_, QPoint(1, 3))
        tree_browser.setFactoryForManager(manager_map[Manager.POINT].subIntPropertyManager(),
                                          factory_map[Factory.INT_EDIT])
        box_browser.setFactoryForManager(manager_map[Manager.POINT].subIntPropertyManager(),
                                         factory_map[Factory.INT_EDIT])
        button_browser.setFactoryForManager(manager_map[Manager.POINT].subIntPropertyManager(),
                                            factory_map[Factory.INT_EDIT])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # pointf
        manager_map[Manager.POINTF].valueChanged.connect(set_value)
        property_ = manager_map[Manager.POINTF].addProperty("pointf")
        property_.propertyManager().setValue(property_, QPointF(1.23, 3.21))
        tree_browser.setFactoryForManager(manager_map[Manager.POINTF].subDoublePropertyManager(),
                                          factory_map[Factory.DOUBLE_EDIT])
        box_browser.setFactoryForManager(manager_map[Manager.POINTF].subDoublePropertyManager(),
                                         factory_map[Factory.DOUBLE_EDIT])
        button_browser.setFactoryForManager(manager_map[Manager.POINTF].subDoublePropertyManager(),
                                            factory_map[Factory.DOUBLE_EDIT])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # size_r
        manager_map[Manager.SIZE].valueChanged.connect(set_value)
        property_ = manager_map[Manager.SIZE].addProperty("size_r")
        property_.propertyManager().setReadOnly(property_, True)
        property_.propertyManager().setMinimum(property_, QSize(0, 0))
        property_.propertyManager().setMaximum(property_, QSize(2, 2))
        property_.propertyManager().setValue(property_, QSize(-1, 3))
        tree_browser.setFactoryForManager(manager_map[Manager.SIZE].subIntPropertyManager(),
                                          factory_map[Factory.INT_EDIT])
        box_browser.setFactoryForManager(manager_map[Manager.SIZE].subIntPropertyManager(),
                                         factory_map[Factory.INT_EDIT])
        button_browser.setFactoryForManager(manager_map[Manager.SIZE].subIntPropertyManager(),
                                            factory_map[Factory.INT_EDIT])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # size_rw
        manager_map[Manager.SIZE].valueChanged.connect(set_value)
        property_ = manager_map[Manager.SIZE].addProperty("size_rw")
        property_.propertyManager().setReadOnly(property_, False)
        property_.propertyManager().setMinimum(property_, QSize(0, 0))
        property_.propertyManager().setMaximum(property_, QSize(255, 255))
        property_.propertyManager().setValue(property_, QSize(-1, 3))
        tree_browser.setFactoryForManager(manager_map[Manager.SIZE].subIntPropertyManager(),
                                          factory_map[Factory.INT_EDIT])
        box_browser.setFactoryForManager(manager_map[Manager.SIZE].subIntPropertyManager(),
                                         factory_map[Factory.INT_EDIT])
        button_browser.setFactoryForManager(manager_map[Manager.SIZE].subIntPropertyManager(),
                                            factory_map[Factory.INT_EDIT])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # sizef_r
        manager_map[Manager.SIZEF].valueChanged.connect(set_value)
        property_ = manager_map[Manager.SIZEF].addProperty("sizef_r")
        property_.propertyManager().setReadOnly(property_, True)
        property_.propertyManager().setMinimum(property_, QSize(0, 0))
        property_.propertyManager().setMaximum(property_, QSize(2, 2))
        property_.propertyManager().setValue(property_, QSizeF(-1.23, 3.21))
        tree_browser.setFactoryForManager(manager_map[Manager.SIZEF].subDoublePropertyManager(),
                                          factory_map[Factory.DOUBLE_EDIT])
        box_browser.setFactoryForManager(manager_map[Manager.SIZEF].subDoublePropertyManager(),
                                         factory_map[Factory.DOUBLE_EDIT])
        button_browser.setFactoryForManager(manager_map[Manager.SIZEF].subDoublePropertyManager(),
                                            factory_map[Factory.DOUBLE_EDIT])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # sizef_rw
        manager_map[Manager.SIZEF].valueChanged.connect(set_value)
        property_ = manager_map[Manager.SIZEF].addProperty("sizef_rw")
        property_.propertyManager().setReadOnly(property_, False)
        property_.propertyManager().setMinimum(property_, QSize(0, 0))
        property_.propertyManager().setMaximum(property_, QSize(2, 2))
        property_.propertyManager().setValue(property_, QSizeF(-1.23, 3.21))
        tree_browser.setFactoryForManager(manager_map[Manager.SIZEF].subDoublePropertyManager(),
                                          factory_map[Factory.DOUBLE_EDIT])
        box_browser.setFactoryForManager(manager_map[Manager.SIZEF].subDoublePropertyManager(),
                                         factory_map[Factory.DOUBLE_EDIT])
        button_browser.setFactoryForManager(manager_map[Manager.SIZEF].subDoublePropertyManager(),
                                            factory_map[Factory.DOUBLE_EDIT])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # rect
        manager_map[Manager.RECT].valueChanged.connect(set_value)
        property_ = manager_map[Manager.RECT].addProperty("rect")
        property_.propertyManager().setValue(property_, QRect(0, 1, 2, 3))
        tree_browser.setFactoryForManager(manager_map[Manager.RECT].subIntPropertyManager(),
                                          factory_map[Factory.INT_EDIT])
        box_browser.setFactoryForManager(manager_map[Manager.RECT].subIntPropertyManager(),
                                         factory_map[Factory.INT_EDIT])
        button_browser.setFactoryForManager(manager_map[Manager.RECT].subIntPropertyManager(),
                                            factory_map[Factory.INT_EDIT])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # rectf
        manager_map[Manager.RECTF].valueChanged.connect(set_value)
        property_ = manager_map[Manager.RECTF].addProperty("rectf")
        property_.propertyManager().setValue(property_, QRectF(0.12, 1.23, 2.34, 3.45))
        tree_browser.setFactoryForManager(manager_map[Manager.RECTF].subDoublePropertyManager(),
                                          factory_map[Factory.DOUBLE_EDIT])
        box_browser.setFactoryForManager(manager_map[Manager.RECTF].subDoublePropertyManager(),
                                         factory_map[Factory.DOUBLE_EDIT])
        button_browser.setFactoryForManager(manager_map[Manager.RECTF].subDoublePropertyManager(),
                                            factory_map[Factory.DOUBLE_EDIT])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # enum
        value = Color.RED
        manager_map[Manager.ENUM].valueChanged.connect(set_value)
        property_ = manager_map[Manager.ENUM].addProperty("enum")
        items = sorted(value.__class__.__members__.items(), key=lambda t: t[1].value)
        names = [k for k, v in items]
        manager_map[Manager.ENUM].setEnumNames(property_, names)
        try:
            manager_map[Manager.ENUM].setValue(property_, value.value)
        except AttributeError:
            manager_map[Manager.ENUM].setValue(property_, value)
        tree_browser.setFactoryForManager(manager_map[Manager.ENUM], factory_map[Factory.ENUM])
        box_browser.setFactoryForManager(manager_map[Manager.ENUM], factory_map[Factory.ENUM])
        button_browser.setFactoryForManager(manager_map[Manager.ENUM], factory_map[Factory.ENUM])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # flags
        value = ColorCombiner.PURPLE
        manager_map[Manager.FLAG].valueChanged.connect(set_value)
        property_ = manager_map[Manager.FLAG].addProperty("flag")
        items = value.__class__.__members__.items()
        names = [k for ind, (k, v) in enumerate(items) if (v.value & (v.value - 1)) == 0 and v.value != 0]
        manager_map[Manager.FLAG].setFlagNames(property_, names)
        try:
            manager_map[Manager.FLAG].setValue(property_, value.value)
        except AttributeError:
            manager_map[Manager.FLAG].setValue(property_, value)
        tree_browser.setFactoryForManager(manager_map[Manager.FLAG].subBoolPropertyManager(),
                                          factory_map[Factory.BOOL])
        box_browser.setFactoryForManager(manager_map[Manager.FLAG].subBoolPropertyManager(),
                                         factory_map[Factory.BOOL])
        button_browser.setFactoryForManager(manager_map[Manager.FLAG].subBoolPropertyManager(),
                                            factory_map[Factory.BOOL])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # size_policy
        manager_map[Manager.SIZE_POLICY].valueChanged.connect(set_value)
        property_ = manager_map[Manager.SIZE_POLICY].addProperty("size_policy")
        property_.propertyManager().setValue(property_, QSizePolicy())
        tree_browser.setFactoryForManager(manager_map[Manager.SIZE_POLICY].subEnumPropertyManager(),
                                          factory_map[Factory.ENUM])
        tree_browser.setFactoryForManager(manager_map[Manager.SIZE_POLICY].subIntPropertyManager(),
                                          factory_map[Factory.INT_EDIT])
        box_browser.setFactoryForManager(manager_map[Manager.SIZE_POLICY].subEnumPropertyManager(),
                                         factory_map[Factory.ENUM])
        box_browser.setFactoryForManager(manager_map[Manager.SIZE_POLICY].subIntPropertyManager(),
                                         factory_map[Factory.INT_EDIT])
        button_browser.setFactoryForManager(manager_map[Manager.SIZE_POLICY].subEnumPropertyManager(),
                                            factory_map[Factory.ENUM])
        button_browser.setFactoryForManager(manager_map[Manager.SIZE_POLICY].subIntPropertyManager(),
                                            factory_map[Factory.INT_EDIT])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # font
        manager_map[Manager.FONT].valueChanged.connect(set_value)
        property_ = manager_map[Manager.FONT].addProperty("font")
        property_.propertyManager().setValue(property_, QFont())
        tree_browser.setFactoryForManager(manager_map[Manager.FONT], factory_map[Factory.FONT])
        box_browser.setFactoryForManager(manager_map[Manager.FONT], factory_map[Factory.FONT])
        button_browser.setFactoryForManager(manager_map[Manager.FONT], factory_map[Factory.FONT])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # color
        manager_map[Manager.COLOR].valueChanged.connect(set_value)
        property_ = manager_map[Manager.COLOR].addProperty("color")
        property_.propertyManager().setValue(property_, QColor())
        tree_browser.setFactoryForManager(manager_map[Manager.COLOR], factory_map[Factory.COLOR])
        box_browser.setFactoryForManager(manager_map[Manager.COLOR], factory_map[Factory.COLOR])
        button_browser.setFactoryForManager(manager_map[Manager.COLOR], factory_map[Factory.COLOR])
        browser_item = tree_browser.addProperty(property_)
        tree_browser.setExpanded(browser_item, False)
        browser_item = box_browser.addProperty(property_)
        browser_item = button_browser.addProperty(property_)
        button_browser.setExpanded(browser_item, False)

        # cursor
        manager_map[Manager.CURSOR].valueChanged.connect(set_value)
        property_ = manager_map[Manager.CURSOR].addProperty("cursor")
        property_.propertyManager().setValue(property_, QCursor())
        tree_browser.setFactoryForManager(manager_map[Manager.CURSOR], factory_map[Factory.CURSOR])
        box_browser.setFactoryForManager(manager_map[Manager.CURSOR], factory_map[Factory.CURSOR])
        button_browser.setFactoryForManager(manager_map[Manager.CURSOR], factory_map[Factory.CURSOR])
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
