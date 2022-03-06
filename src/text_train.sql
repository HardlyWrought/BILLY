CREATE TABLE IF NOT EXISTS "emission_count"
		("word"  TEXT,
		 "tag"   TEXT,
		 "count" INTEGER DEFAULT 0,
		 "total" INTEGER DEFAULT 0,
		 "odds"  REAL DEFAULT 0.0,
		 PRIMARY KEY ("word", "tag")
);

CREATE TABLE IF NOT EXISTS "transition_count"
		("tag"      TEXT,
		 "next_tag" TEXT,
		 "count"    INTEGER DEFAULT 0,
		 "total"    INTEGER DEFAULT 0,
		 "odds"     REAL DEFAULT 0.0,
		 PRIMARY KEY ("tag", "next_tag")
);


--from main program--


INSERT OR IGNORE INTO "emission_count" ("word", "tag")
VALUES (?, ?);

UPDATE "emission_count"
SET "count" = "count" + 1
WHERE "word" = ? AND "tag" = ?;

--while (sqlite3_step(&stmt) == SQLITE_ROW
UPDATE "emission_count"
SET "total" = "total" + 1
WHERE "word" = ?;

INSERT OR IGNORE INTO "transition_count" ("tag, next_tag")
VALUES (?, ?)

UPDATE "transition_count"
SET "count" = "count" + 1
WHERE "tag" = ? AND "next_tag" = ?;

--while (sqlite3_step(&stmt) == SQLITE_ROW
UPDATE "transition_count"
SET "total" = "total" + 1
WHERE "word" = ?;


--after main program--


BEGIN TRANSACTION;
DELETE FROM "emission_count"
WHERE "count" = 0;

DELETE FROM "transition_count"
WHERE "count" = 0;

UPDATE "emission_count"
SET "odds" = CAST("count" AS REAL) / "total";

UPDATE "transition_count"
SET "odds" = CAST("count" AS REAL) / "total";
END TRANSACTION;


CREATE TABLE "emission"
AS SELECT "word", "tag", "odds"
FROM "emissions"
WHERE "odds" > .01 AND "total" > 5 ORDER BY "total" DESC, "word" DESC, "odds" DESC, "tag" DESC;

CREATE TABLE "transition"
AS SELECT "tag", "next_tag", "odds"
FROM "transitions"
WHERE "odds" > .001 ORDER BY "total" DESC, "tag" DESC, "odds" DESC, "next_tag" DESC;

DROP TABLE "emission_count";
DROP TABLE "transition_count";


BEGIN TRANSACTION;
UPDATE "emission"   SET "odds" = ROUND("odds", 4);
UPDATE "transition" SET "odds" = ROUND("odds", 4);
UPDATE "emission"   SET "odds" = 1.0 WHERE "odds" >= .99;
UPDATE "transition" SET "odds" = 1.0 WHERE "odds" >= .999;
END TRANSACTION;

BEGIN TRANSACTION;
DELETE FROM "emission"
WHERE "word" NOT IN
			(SELECT DISTINCT "word"
			 FROM "emission"
			 LIMIT 50000);
END TRANSACTION;
