#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/of_device.h>
#ifdef CONFIG_SHUB_MODULE
#include <linux/module.h>
#endif
#include "shub_device.h"
#include "../utility/shub_utility.h"

static const struct dev_pm_ops shub_pm_ops = {
	.prepare = shub_suspend,
	.complete = shub_resume,
};

static struct of_device_id shub_match_table[] = {
	{
		.compatible = "shub"
	},
};

static struct platform_driver shub_driver = {
	.probe = shub_probe,
	.shutdown = shub_shutdown,
	.driver = {
		.pm = &shub_pm_ops,
		.owner = THIS_MODULE,
		.name = "shub",
		.of_match_table = shub_match_table
	},
};

#ifdef CONFIG_SHUB_MODULE
static int __init shub_init(void)
{
	int ret = 0;
	shub_infof();
	ret = platform_driver_register(&shub_driver);

	shub_infof("ret %d", ret);
	return ret;
}

static void __exit shub_exit(void)
{
	platform_driver_unregister(&shub_driver);
}

late_initcall(shub_init);
module_exit(shub_exit);
MODULE_DESCRIPTION("(Sensor Hub)SHUB dev driver");
MODULE_AUTHOR("Samsung Electronics");
MODULE_LICENSE("GPL");
#else
static void *shub_drvdata;

int sensorhub_device_probe(struct platform_device *pdev)
{
	int ret;
	void *ori_drvdata = platform_get_drvdata(pdev);

	if ((ret = shub_driver.probe(pdev)) >= 0) {
		shub_drvdata = platform_get_drvdata(pdev);
	}
	platform_set_drvdata(pdev, ori_drvdata);
	return ret;
}

void sensorhub_device_shutdown(struct platform_device *pdev)
{
	void *ori_drvdata = platform_get_drvdata(pdev);

	platform_set_drvdata(pdev, shub_drvdata);
	shub_driver.shutdown(pdev);
	platform_set_drvdata(pdev, ori_drvdata);
}

int sensorhub_device_prepare(struct device *dev)
{
	int ret;
	struct platform_device *pdev = to_platform_device(dev);
	void *ori_drvdata = platform_get_drvdata(pdev);

	platform_set_drvdata(pdev, shub_drvdata);
	ret = shub_driver.driver.pm->prepare(dev);
	platform_set_drvdata(pdev, ori_drvdata);
	return ret;
}

void sensorhub_device_complete(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	void *ori_drvdata = platform_get_drvdata(pdev);

	platform_set_drvdata(pdev, shub_drvdata);
	shub_driver.driver.pm->complete(dev);
	platform_set_drvdata(pdev, ori_drvdata);
}
#endif /* CONFIG_SHUB_MODULE */
