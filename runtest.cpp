#include <gtest/gtest.h>
#include "../server/Config/config.h"
#include "../server/Model/adminUser.h"
#include "../server/Model/announcement.h"
#include "../server/Main/main.h"

// 初始化测试
class SystemIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 初始化配置或模拟数据
        config = Config();
        adminUser = AdminUser("admin", "password");
        announcement = Announcement();
    }

    void TearDown() override {
        // 清理资源
    }

    Config config;
    AdminUser adminUser;
    Announcement announcement;
};

// 测试配置加载
TEST_F(SystemIntegrationTest, ConfigLoadTest) {
    ASSERT_TRUE(config.loadConfig("../config/config.json"));
}

// 测试管理员用户创建和权限
TEST_F(SystemIntegrationTest, AdminUserTest) {
    EXPECT_EQ(adminUser.getUsername(), "admin");
    EXPECT_TRUE(adminUser.verifyPassword("password"));

    adminUser.setPermission("read", true);
    EXPECT_TRUE(adminUser.hasPermission("read"));
}

// 测试公告模块
TEST_F(SystemIntegrationTest, AnnouncementTest) {
    announcement.setTitle("Test Announcement");
    announcement.setContent("This is a test announcement.");

    EXPECT_EQ(announcement.getTitle(), "Test Announcement");
    EXPECT_EQ(announcement.getContent(), "This is a test announcement.");

    announcement.publish();
    EXPECT_TRUE(announcement.isPublished());
}

// 测试系统主模块
TEST_F(SystemIntegrationTest, MainModuleTest) {
    // 模拟系统初始化
    ASSERT_NO_THROW(main::initializeSystem());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

