from conan import ConanFile


class Test(ConanFile):
    generators =("CMakeToolchain", "CMakeDeps")
    settings = ("os", "build_type", "arch", "compiler")
    
    def requirements(self):
        self.requires("fmt/10.2.1")
        self.requires("range-v3/0.12.0")
        self.requires("melon/0.5")
    
    def build_requirements(self):
        self.tool_requires("cmake/[>=3.16.3]")
        
    def layout(self):
        self.folders.generators = ""