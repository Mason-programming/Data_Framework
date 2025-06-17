import os
import sys
import byp
from pxr import Usd, UsdGeom
from src.bridge_scripts.sessionManager import sessionManager
class detect_changes:
    def __init__(self):
        self.session = sessionManager()

    def state(self):
        s = [True, False]
        return s

    def load_in_changes(self):

        if self.state()[0]:
            stage = self.session.get_current_stage()
            stage 


