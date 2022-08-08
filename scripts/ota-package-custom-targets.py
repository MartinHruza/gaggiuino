import os

Import("env")

dependecy_envs = env.GetProjectOption("custom_depends_on")

dependecy_fw_paths = []
for dep in list(dependecy_envs.split(",")):
  dependecy_fw_paths.append(os.path.join("$PROJECT_BUILD_DIR", dep.strip(), "firmware.bin"))

script_path = os.path.join("$PROJECT_DIR", "scripts", "combine_fw.py")
command = "\"$PYTHONEXE\" \"" + script_path + "\" \"" + os.path.join("$PROJECT_BUILD_DIR", "$PIOENV", "firmware.bin") + "\""
for fw in dependecy_fw_paths:
  command = command + " " + "\"" + fw + "\""

env.AddCustomTarget(
    name="combine_firmware_files",
    dependencies=dependecy_fw_paths,
    actions=command,
    title="Combine firmware files",
    description="Combine firmware for backend and fronted into a single OTA firmware file"
)

#print(env.Dump())
