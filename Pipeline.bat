@echo off

for %%d in (*.pvr) do GOTO continue

pngquant -f --skip-if-larger --ext .png *.png

optipng *.png

for %%f in (*.png) do PVRTexToolCLI.exe -i "%%f" -f r8g8b8a8

:continue