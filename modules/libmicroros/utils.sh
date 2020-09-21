update_meta() {
      python3 -c "import sys; import json; c = '-D' +'$2'; s = json.loads(''.join([l for l in sys.stdin])); k = s['names']['$1']['cmake-args']; i = [c.startswith(v.split('=')[0]) for v in k]; k.pop(i.index(True)) if any(i) else None; k.append(c) if len(c.split('=')[1]) else None; print(json.dumps(s,indent=4))" < $COMPONENT_PATH/configured_colcon.meta > $COMPONENT_PATH/configured_colcon_new.meta
      mv $COMPONENT_PATH/configured_colcon_new.meta $COMPONENT_PATH/configured_colcon.meta
}

remove_meta() {
      python3 -c "import sys; import json; c = '-D' +'$2'; s = json.loads(''.join([l for l in sys.stdin])); k = s['names']['$1']['cmake-args']; i = [c.startswith(v.split('=')[0]) for v in k]; k.pop(i.index(True)) if any(i) else None; print(json.dumps(s,indent=4))" < $COMPONENT_PATH/configured_colcon.meta > $COMPONENT_PATH/configured_colcon_new.meta
      mv $COMPONENT_PATH/configured_colcon_new.meta $COMPONENT_PATH/configured_colcon.meta
}

update_meta_from_zephyr_config() {
      AUX_VARIABLE=$(grep $1 $ZEPHYR_CONF_FILE | awk -F '=' '{gsub(/"/, "", $2); print $2}'); \
      update_meta "$2" "$3=$AUX_VARIABLE"; \
}
