#pragma once

#include <fstream>
#include <format>
#include <string>
#include <set>
#include <vector>

#include "RFDefine.h"
#include "Logger.h"
#include "Assert.h"

#if !defined(RF_NO_LOG)
#define RF_ENABLE_LOG(LogCategory) rf::LogDispatcher::Instance().EnableCategory(LogCategory, true)
#define RF_DISABLE_LOG(LogCategory) rf::LogDispatcher::Instance().EnableCategory(LogCategory, false)

#define RF_LOG_DEBUG(Category, Message) rf::LogDispatcher::Instance().Debug(Category, Message)
#define RF_LOG_INFO(Category, Message) rf::LogDispatcher::Instance().Info(Category, Message)
#define RF_LOG_WARNING(Category, Message) rf::LogDispatcher::Instance().Warning(Category, Message)
#define RF_LOG_ERROR(Category, Message) \
    do { \
        const auto formatted = std::format("({}:{}) {}", __FILE__, __LINE__, Message); \
        rf::LogDispatcher::Instance().Error(Category, formatted); \
    } while(0);

#define RF_LOG_FATAL(Category, Message) \
    do { \
        const auto formatted = std::format("({}:{}) {}", __FILE__, __LINE__, Message); \
        rf::LogDispatcher::Instance().Fatal(Category, formatted); \
    } while(0);
#else
#define RF_ENABLE_LOG(LogCategory)
#define RF_DISABLE_LOG(LogCategory)

#define RF_LOG_DEBUG(Category, Message)
#define RF_LOG_INFO(Category, Message)
#define RF_LOG_WARNING(Category, Message)
#define RF_LOG_ERROR(Category, Message)
#define RF_LOG_FATAL(Category, Message)
#endif // !defined(RF_NO_LOG)

#define RF_DECLARE_LOG_EXTERN(LogCategory) extern const std::string Log##LogCategory
#define RF_DEFINE_LOG(LogCategory) const std::string Log##LogCategory = #LogCategory

//! Uncategorized logs.
RF_DECLARE_LOG_EXTERN(Temp);

RF_NAMESPACE
{
    class LogDispatcher final
    {
    public:
        LogDispatcher();
        ~LogDispatcher();

        static void Init();
        static void Destroy();
        static LogDispatcher& Instance();

        void AddLogger(Ref<ILogger> logger);
        void AddLoggers(std::initializer_list<Ref<ILogger>> loggers);
        void Flush() const;

        void Log(LogLevel level, const std::string& category, const std::string& message);

        void Debug(const std::string& category, const std::string& message);
        void Info(const std::string& category, const std::string& message);
        void Warning(const std::string& category, const std::string& message);
        void Error(const std::string& category, const std::string& message);
        /**
         * A fatal error has occurred and the application cannot continue.
         * This will forcefully terminate the app.
         */
        void Fatal(const std::string& category, const std::string& message);

        /**
         * Set the minimum log level and discard all the log below the specified level.
         * @param level Minimum log level. For example, if this parameter is set to @c LogLevel::Warning,
         * any logs from @c LogLevel::Debug and @c LogLevel::Info will be discarded.
         */
        void SetMinumumLogLevel(LogLevel level);
        //! Enable/disable logs from a specific category.
        void EnableCategory(const std::string& category, bool enable);

        RF_NODISCARD const std::string& Message() const
        {
            return m_message;
        }
    private:
        std::vector<Ref<ILogger>> m_loggers;
        std::string m_message;

        LogLevel m_minimumLogLevel = LogLevel::Debug;
        //! A set of disabled log categories.
        std::set<std::string> m_disableLogs;
        /// @brief A connection to the assertion failure signal.
        /// This is used to capture assertion failures and log them appropriately.
        // sigslot::connection m_assertConnection;
    };
}