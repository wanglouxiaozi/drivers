#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xe89b6b83, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xec33210d, __VMLINUX_SYMBOL_STR(single_release) },
	{ 0x4ed703a4, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0xb2c96ed, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0x36ef98b5, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0xd813562f, __VMLINUX_SYMBOL_STR(proc_create_data) },
	{ 0x864d541d, __VMLINUX_SYMBOL_STR(proc_mkdir) },
	{ 0x20000329, __VMLINUX_SYMBOL_STR(simple_strtoul) },
	{ 0x56d4ca56, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0x851a73b5, __VMLINUX_SYMBOL_STR(single_open) },
	{ 0x989e4b76, __VMLINUX_SYMBOL_STR(PDE_DATA) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "E68AF238BE26DF9E628FF4C");
