# 🎬 سیستم مدیریت سینما (Cinema Management System)

یک سیستم مدیریت سینما کامل که با زبان C و پایگاه داده PostgreSQL پیاده‌سازی شده است. این سیستم امکان مدیریت فیلم‌ها، کاربران، سانس‌ها، بلیط‌ها و گزارش‌گیری را فراهم می‌کند.

## 📋 ویژگی‌ها

### 🎥 مدیریت فیلم‌ها (Movie Management)

- افزودن فیلم جدید
- ویرایش اطلاعات فیلم
- حذف فیلم
- نمایش لیست تمام فیلم‌ها
- جستجوی فیلم بر اساس عنوان یا ژانر

### 👥 مدیریت کاربران (User Management)

- ثبت کاربر جدید
- ویرایش اطلاعات کاربر
- حذف کاربر
- نمایش لیست تمام کاربران
- جستجوی کاربر بر اساس نام یا شماره تلفن

### 🎭 مدیریت سانس‌ها (Session Management)

- ایجاد سانس جدید برای فیلم
- ویرایش اطلاعات سانس
- حذف سانس
- نمایش لیست تمام سانس‌ها
- جستجوی سانس بر اساس فیلم

### 🎫 مدیریت بلیط‌ها (Ticket Management)

- خرید بلیط (با بررسی ظرفیت و صندلی)
- لغو بلیط
- نمایش لیست تمام بلیط‌ها
- جستجوی بلیط بر اساس کاربر

### 📊 گزارش‌گیری (Reports)

- تعداد کل بلیط‌های فروخته شده
- فروش بر اساس فیلم
- محبوب‌ترین سانس‌ها
- کاربران فعال
- موجودی بلیط برای هر سانس

## 🛠️ نیازمندی‌ها

- **C Compiler**: GCC یا هر کامپایلر C دیگر
- **PostgreSQL**: نسخه 12 یا بالاتر
- **libpq**: کتابخانه PostgreSQL برای C
- **Docker** (اختیاری): برای اجرای PostgreSQL با Docker Compose

### نصب در Ubuntu/Debian:

```bash
sudo apt-get update
sudo apt-get install postgresql postgresql-contrib libpq-dev gcc
```

### نصب در Windows:

- دانلود و نصب PostgreSQL از [postgresql.org](https://www.postgresql.org/download/windows/)
- دانلود و نصب MinGW یا MSYS2 برای کامپایلر GCC

## 🚀 نصب و راه‌اندازی

### 1. کلون کردن پروژه

```bash
git clone https://github.com/mohammadrezabalooch/cinema_management_C_Postgresql.git
cd cinema_management_C_Postgresql
```

### 2. راه‌اندازی پایگاه داده

#### روش 1: استفاده از Docker Compose (پیشنهادی)

```bash
docker-compose up -d
```

#### روش 2: نصب مستقیم PostgreSQL

```bash
# ایجاد دیتابیس
sudo -u postgres psql
CREATE DATABASE postgres;
\q
```

### 3. کامپایل پروژه

#### در Linux/Mac:

```bash
gcc -o main main.c menus.c queries.c connect_to_psql.c create_tables.c -I/usr/include/postgresql -lpq
```

#### در Windows (MinGW):

```bash
gcc -o main.exe main.c menus.c queries.c connect_to_psql.c create_tables.c -I"C:\Program Files\PostgreSQL\<version>\include" -L"C:\Program Files\PostgreSQL\<version>\lib" -lpq
```

### 4. اجرای برنامه

```bash
./main
# یا در Windows:
main.exe
```

## 📁 ساختار پروژه

```
cinema_management_C_Postgresql/
├── main.c                 # فایل اصلی برنامه
├── menus.c                # پیاده‌سازی منوها
├── menus.h                # هدر منوها
├── queries.c              # توابع کوئری دیتابیس
├── queries.h              # هدر توابع کوئری
├── connect_to_psql.c      # توابع اتصال به دیتابیس
├── connect_to_psql.h      # هدر اتصال
├── create_tables.c        # ایجاد جداول دیتابیس
├── create_tables.h        # هدر ایجاد جداول
├── docker-compose.yml     # تنظیمات Docker Compose
└── README.md              # این فایل
```

## 🗄️ ساختار دیتابیس

### جدول movies (فیلم‌ها)

- `movie_id` (SERIAL PRIMARY KEY)
- `title` (VARCHAR)
- `genre` (VARCHAR)
- `release_year` (INT)

### جدول users (کاربران)

- `user_id` (SERIAL PRIMARY KEY)
- `name` (VARCHAR)
- `phone` (VARCHAR)

### جدول sessions (سانس‌ها)

- `session_id` (SERIAL PRIMARY KEY)
- `movie_id` (INT, FOREIGN KEY)
- `session_time` (TIMESTAMP)
- `hall` (INT)
- `capacity` (INT)

### جدول tickets (بلیط‌ها)

- `ticket_id` (SERIAL PRIMARY KEY)
- `user_id` (INT, FOREIGN KEY)
- `session_id` (INT, FOREIGN KEY)
- `seat_number` (INT)

## 💻 نحوه استفاده

پس از اجرای برنامه، منوی اصلی نمایش داده می‌شود:

```
===========================================
          Cinema Management System
===========================================
1. Movie Management
2. User Management
3. Session Management
4. Ticket Management
5. Reports
0. Exit
```

هر بخش دارای منوی فرعی خود است که امکان انجام عملیات CRUD را فراهم می‌کند.

### مثال: افزودن فیلم

1. از منوی اصلی گزینه `1` را انتخاب کنید
2. از منوی Movie Management گزینه `1` را انتخاب کنید
3. اطلاعات فیلم را وارد کنید:
   - عنوان فیلم
   - ژانر
   - سال انتشار

## 🔧 تنظیمات اتصال

در صورت نیاز به تغییر تنظیمات اتصال به دیتابیس، فایل `connect_to_psql.c` را ویرایش کنید:

```c
const char *conninfo =
    "host=localhost port=5432 dbname=postgres user=postgres";
```

## 🐛 عیب‌یابی

### مشکل: "Database connection failed"

- مطمئن شوید PostgreSQL در حال اجرا است
- بررسی کنید که پورت 5432 باز است
- در صورت استفاده از Docker، بررسی کنید container در حال اجرا است

### مشکل: "Table creation failed"

- بررسی کنید که دیتابیس `postgres` وجود دارد
- بررسی کنید که کاربر `postgres` دسترسی دارد

### مشکل: خطای کامپایل "libpq-fe.h: No such file"

- مطمئن شوید `libpq-dev` نصب شده است
- مسیر include را در دستور کامپایل بررسی کنید

## 📝 توابع اصلی

### توابع اتصال (connect_to_psql.c)

- `connect_to_db()`: اتصال به دیتابیس PostgreSQL
- `execute_sql()`: اجرای دستورات SQL (INSERT, UPDATE, DELETE)
- `execute_sql_query()`: اجرای کوئری‌های SELECT

### توابع کوئری (queries.c)

- **Movie**: `add_movie()`, `edit_movie()`, `delete_movie()`, `list_movies()`, `search_movie()`
- **User**: `add_user()`, `edit_user()`, `delete_user()`, `list_users()`, `search_user()`
- **Session**: `create_session()`, `edit_session()`, `delete_session()`, `list_sessions()`, `search_session()`
- **Ticket**: `buy_ticket()`, `cancel_ticket()`, `list_tickets()`, `search_ticket()`
- **Reports**: `get_total_sales()`, `get_sales_by_movie()`, `get_popular_sessions()`, `get_active_users()`, `get_ticket_availability()`

## 🤝 مشارکت

برای مشارکت در پروژه:

1. Fork کنید
2. یک برنچ جدید ایجاد کنید (`git checkout -b feature/AmazingFeature`)
3. تغییرات را کامیت کنید (`git commit -m 'Add some AmazingFeature'`)
4. Push کنید (`git push origin feature/AmazingFeature`)
5. یک Pull Request باز کنید

## 👤 نویسنده

**Mohammad Reza Balooch**

- GitHub: [@mohammadrezabalooch](https://github.com/mohammadrezabalooch)

---

⭐ اگر این پروژه برایتان مفید بود، لطفاً یک ستاره بدهید!
