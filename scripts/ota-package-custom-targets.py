import os
Import("env")

def safe_path_decor(path_string):
  return "\""+path_string+"\""

dependecy_envs = env.GetProjectOption("custom_depends_on")

dependencies = {}
for dep in list(dependecy_envs.split(",")):
  priority = dep.split(':')[0].strip()
  dependecy_name = dep.split(':')[1].strip()

  dependencies[priority] = list()
  dependencies[priority].append(dependecy_name)
  dependencies[priority].append(os.path.join("$PROJECT_BUILD_DIR", dependecy_name, "firmware.bin"))


script_path = os.path.join("$PROJECT_DIR", "scripts", "combine_fw.py")
command = safe_path_decor("$PYTHONEXE") + " " + safe_path_decor(script_path) + " " + safe_path_decor(os.path.join("$PROJECT_BUILD_DIR", "$PIOENV", "firmware.bin"))
for prio, list_of_vals in dependencies.items():
  command = command + " " + safe_path_decor(prio + ":" + list_of_vals[1])

dependecy_fw_paths = []
for prio, list_of_vals in dependencies.items():
  dependecy_fw_paths.append(list_of_vals[1])

env.AddCustomTarget(
    name="combine_firmware_files",
    dependencies=dependecy_fw_paths,
    actions=command,
    title="Combine firmware files",
    description="Combine firmware for backend and fronted into a single OTA firmware file"
)

#print(env.Dump())
