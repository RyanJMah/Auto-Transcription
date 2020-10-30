from setuptools import setup

setup(
    name = "main.py",
    version = "0.0.1",
    py_modules = ["main"],
    install_requires = [
        "Click",
        "matplotlib"
    ],
    entry_points = """
        [console_scripts]
        plot_csv=main:plot_csv
    """


)
