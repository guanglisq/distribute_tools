# -*- coding: utf-8 -*-

from PyQt5.QtCore import pyqtSlot as Slot
from PyQt5 import QtCore
from PyQt5 import QtWidgets
from PyQt5 import QtSql
import os

class createCfgFile():
    def __init__(self):
        self.opts = {
            'author'                    : 'LiGuang',
            'licenseFile'               : 'COPYING',
            'nodeName'                  : 'RosReworks',
            'includeDir'                : '.',
            'sourceDir'                 : '.',
            'qosConfigFilename'         : 'demo',
            'genMsgTypesHeader'         : 'true',
            'genMsgTypesSource'         : 'true',
            'genHandlersHeader'         : 'true',
            'genHandlersSource'         : 'true',
            'genQosConfigHeader'        : 'true',
        }
        self.db=None
        self.itemTabl=None
        pass
    def qosconfig_header_path(self):
        path =  os.getcwd() + os.sep + self.opts['includeDir'];
        return os.path.normpath(path + os.sep + self.opts['qosConfigFilename'] + '.cfg')
    def export_qosconfig_header(self,text):
        with open(self.qosconfig_header_path(), 'w') as f:
            f.write(text)
    def gen_qosconfig_header(self):
        text = '# This is the options section. All the options are assigned below. An undefined\n'
        text += '# option is assigned its default value. Run rerosgen.py without arguments to see\n'
        text += '# their default values.\n[Options]\n\n# Author of the generated files\n'
        text += 'author                      = %s\n\n' % self.opts['author']
        text += '# Optional license text file to comment at the beginning of generated files\nlicenseFile                 = %s\n\n' % self.opts['licenseFile']
        text += '# Name of the generated node\nnodeName                    = %s\n\n' % self.opts['nodeName']
        text += '# Paths of the generated files, relative to this configuration file\n'
        text += 'includeDir                  = ./code         # Header files path (must exist!)\n'
        text += 'sourceDir                   = ./code         # Source files path (must exist!)\n\n'
        text += '# File names for "<filename>.h" and "<filename>.c" generation\n'
        text += 'msgTypesFilename    = rerosMsgTypes          # Message types file name\n'
        text += 'handlersFilename    = rerosHandlers          # Handlers file name\n\n'
        text += '# Generation switches\ngenMsgTypesHeader   = %s\n' % self.opts['genMsgTypesHeader']
        text += 'genMsgTypesSource   = %s\n' % self.opts['genMsgTypesSource']
        text += 'genHandlersHeader   = %s\n' % self.opts['genHandlersHeader']
        text += 'genHandlersSource   = %s\n' % self.opts['genHandlersSource']
        text += 'genQosConfigHeader   = %s\n\n' % self.opts['genQosConfigHeader']
        text += '# Generates comments above the declaration of each structure field\nfieldComments               = false\n\n'
        return text
    def gen_qosconfig_text(self, text):
        text += '# List of published topics, in the form: <name> = <type>\n[PubTopics]\n'
        self.itemTabl.setTable("pub")
        self.itemTabl.select()
        for i in range(self.itemTabl.rowCount()):
            text += '%s                    = %s\n\n' % (self.itemTabl.record(i).value(1), self.itemTabl.record(i).value(2))
        text += '# List of subscribed topics, in the form: <name> = <type>\n[SubTopics]\n'
        self.itemTabl.setTable("sub")
        self.itemTabl.select()
        for i in range(self.itemTabl.rowCount()):
            text += '%s                    = %s\n\n' % (self.itemTabl.record(i).value(1), self.itemTabl.record(i).value(2))
        text += '# List of published services, in the form: <name> = <type>\n[PubServices]\n'
        self.itemTabl.setTable("reg")
        self.itemTabl.select()
        for i in range(self.itemTabl.rowCount()):
            text += '%s                    = %s\n\n' % (self.itemTabl.record(i).value(1), self.itemTabl.record(i).value(2))
        text += '# List of services called by the node, in the form: <name> = <type>\n[CallServices]\n'
        self.itemTabl.setTable("call")
        self.itemTabl.select()
        for i in range(self.itemTabl.rowCount()):
            text += '%s                    = %s\n\n' % (self.itemTabl.record(i).value(1), self.itemTabl.record(i).value(2))
        text += '# List of qosconfig called by the node, in the form: <name> = <type>\n[qosconfig]\n'
        self.itemTabl.setTable("parameter")
        self.itemTabl.select()
        for i in range(self.itemTabl.rowCount()):
            text += '%s                    = %s\n' % (self.itemTabl.record(i).value(1), self.itemTabl.record(i).value(2))
        return text
    def gen(self):
        if QtSql.QSqlDatabase.contains("qt_sql_default_connection") == True:
            self.db = QtSql.QSqlDatabase.database("qt_sql_default_connection")
        self.db.setDatabaseName(":distribute:")
        if self.db.open() == False:
            print "db open false"
        self.itemTabl = QtSql.QSqlTableModel()
        self.itemTabl.setEditStrategy(QtSql.QSqlTableModel.OnFieldChange)
        text_gen = self.gen_qosconfig_header()
        text_gen = self.gen_qosconfig_text(text_gen)
        self.export_qosconfig_header(text_gen)
        self.db.close

def main():
    cfg = createCfgFile()
    cfg.gen()

