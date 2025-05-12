#!/bin/bash -e

a2enmod php8.1

OT_DB_HOST="${OT_DB_HOST:-db}"
OT_DB_PORT="${OT_DB_PORT:-3306}"
OT_DB_USER="${OT_DB_USER:-tfsuser}"
OT_DB_PASSWORD="${OT_DB_PASSWORD:-StrongUserPassword!}"
OT_DB_DATABASE="${OT_DB_DATABASE:-tibiacore}"


echo ""
echo "===== Installing TibiaCore DataBase ====="
echo ""
sleep 5s
echo ""
echo ".."
echo "...."
echo "......"
echo "........"

until mysql -u "$OT_DB_USER" -p"$OT_DB_PASSWORD" -h "$OT_DB_HOST" --port="$OT_DB_PORT" -e "SHOW DATABASES;"; do
	echo "DB offline, trying again"
	sleep 5s
done

if mysql -u "$OT_DB_USER" -p"$OT_DB_PASSWORD" -h "$OT_DB_HOST" --port="$OT_DB_PORT" -e "use $OT_DB_DATABASE"; then
	echo "Creating Database Backup"
	echo "Saving database to all_databases.sql"
	mysqldump -u "$OT_DB_USER" -p"$OT_DB_PASSWORD" -h "$OT_DB_HOST" --port="$OT_DB_PORT" --all-databases > /tibiacore/data/all_databases.sql
else
	echo "Creating Database"
	mysql -u "$OT_DB_USER" -p"$OT_DB_PASSWORD" -h "$OT_DB_HOST" --port="$OT_DB_PORT" -e "CREATE DATABASE $OT_DB_DATABASE;"
	mysql -u "$OT_DB_USER" -p"$OT_DB_PASSWORD" -h "$OT_DB_HOST" --port="$OT_DB_PORT" -e "SHOW DATABASES;"
fi

echo ""
echo "===== Check If We Need To Import Schema.sql ====="
echo ""

if [[ $(mysql -u "$OT_DB_USER" -p"$OT_DB_PASSWORD" -h "$OT_DB_HOST" -e 'SHOW TABLES LIKE "server_config"' -D "$OT_DB_DATABASE") ]]; then
	echo "Table server_config exists so we don't need to import"
else
	echo "Importing DataBase"
	mysql -u "$OT_DB_USER" -p"$OT_DB_PASSWORD" -h "$OT_DB_HOST" --port="$OT_DB_PORT" -D "$OT_DB_DATABASE" < tibiacore-empty.sql
fi

echo ""
echo "===== Start Server ====="
echo ""

# screen ./restart.sh # Removed this line
