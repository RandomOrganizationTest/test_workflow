from conans import ConanFile
import json
import os

class Installer(ConanFile):
    name = "installer"
    version = "1.0.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "txt"

    def imports(self):
        self.copy("cpp-server", src="bin", dst="bin")
        self.copy("*.so", src="lib", dst="lib")
        libs = []
        for lib in os.listdir("lib"):
            libs.append(os.path.join(os.path.abspath(self.install_folder), "lib", lib))
        configuration_datas = {}
        with open(os.path.join(self.recipe_folder, "configuration.json"), 'r') as configuration:
            file_str = configuration.read()
            file_str = file_str.replace("${src_path}", self.recipe_folder)
            configuration_datas = json.loads(file_str)
        configuration_datas["plugins"] = libs
        with open(os.path.join(self.install_folder, "configuration.json"), 'w') as configuration:
            json.dump(configuration_datas, configuration, indent=4)

    def requirements(self):
        self.requires("route-token-generate-professional/[^1.0.0, loose=False]@obspher/stable")
        self.requires("route-order-deliveries-get/[^1.0.0, loose=False]@obspher/stable")
        self.requires("cpp-server/[^3.0.0, loose=False]@obspher/stable")