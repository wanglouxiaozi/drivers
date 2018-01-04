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
	{ 0xbc34c6e7, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xdbe75f86, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0xdb7305a1, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
	{ 0x2deaccdc, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0x10f6a7ee, __VMLINUX_SYMBOL_STR(cdev_init) },
	{ 0xb441b7f5, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0x97f148ec, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0x621ce347, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x4c3ebbc, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xd8e484f0, __VMLINUX_SYMBOL_STR(register_chrdev_region) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xbec43ad6, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0xfee99811, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0xda589180, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0x4f6b400b, __VMLINUX_SYMBOL_STR(_copy_from_user) },
	{ 0x4f8b5ddb, __VMLINUX_SYMBOL_STR(_copy_to_user) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "750F05CC3B71DC416575784");
