-- -----------------------------------------------------
-- Table `themes`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `themes` ;

CREATE  TABLE IF NOT EXISTS `themes` (
  `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT ,
  `name` VARCHAR(20) NULL ,
  `description` TEXT NULL ) ;


-- -----------------------------------------------------
-- Table `publishers`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `publishers` ;

CREATE  TABLE IF NOT EXISTS `publishers` (
  `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT ,
  `name` VARCHAR(45) NULL ,
  `description` TEXT NULL ,
  `critique` TEXT NULL ,
  `picture` VARCHAR(256) NULL ) ;


-- -----------------------------------------------------
-- Table `authors`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `authors` ;

CREATE  TABLE IF NOT EXISTS `authors` (
  `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT ,
  `firstname` VARCHAR(45) NULL ,
  `lastname` VARCHAR(45) NULL ,
  `description` TEXT NULL ,
  `critique` TEXT NULL ,
  `rating` INT(3) NULL ,
  `picture` VARCHAR(256) NULL ) ;


-- -----------------------------------------------------
-- Table `publishersthemes`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `publishersthemes` ;

CREATE  TABLE IF NOT EXISTS `publishersthemes` (
  `publishersid` INTEGER NOT NULL ,
  `themesid` INTEGER NOT NULL ,
  PRIMARY KEY (`publishersid`, `themesid`) ,
  CONSTRAINT `fk_publishersthemes_publishers`
    FOREIGN KEY (`publishersid` )
    REFERENCES `publishers` (`id` )
  CONSTRAINT `fk_publishersthemes_themes`
    FOREIGN KEY (`themesid` )
    REFERENCES `themes` (`id` ) ) ;


-- -----------------------------------------------------
-- Table `books`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `books` ;

CREATE  TABLE IF NOT EXISTS `books` (
  `id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT ,
  `isbn` CHAR(13) NULL ,
  `title` TEXT NULL ,
  `edition` INT(7) NULL ,
  `description` TEXT NULL ,
  `critique` TEXT NULL ,
  `rating` INT(3) NULL ,
  `cover` VARCHAR(256) NULL ,
  `ebook` VARCHAR(256) NULL ,
  `publishingyear` YEAR NULL ,
  `udc` VARCHAR(20) NULL ,
  CONSTRAINT `translator`
    FOREIGN KEY (`id` )
    REFERENCES `authors` (`id` ) ) ;


-- -----------------------------------------------------
-- Table `booksauthors`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `booksauthors` ;

CREATE  TABLE IF NOT EXISTS `booksauthors` (
  `booksid` INTEGER NOT NULL ,
  `authorsid` INTEGER NOT NULL ,
  PRIMARY KEY (`booksid`, `authorsid`) ,
  CONSTRAINT `fk_booksauthors_books`
    FOREIGN KEY (`booksid` )
    REFERENCES `books` (`id` ),
  CONSTRAINT `fk_booksauthors_authors`
    FOREIGN KEY (`authorsid` )
    REFERENCES `authors` (`id` ) ) ;


-- -----------------------------------------------------
-- Table `authorsthemes`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `authorsthemes` ;

CREATE  TABLE IF NOT EXISTS `authorsthemes` (
  `authorsid` INTEGER NOT NULL ,
  `themesid` INTEGER NOT NULL ,
  PRIMARY KEY (`authorsid`, `themesid`) ,
  CONSTRAINT `fk_authorsthemes_authors`
    FOREIGN KEY (`authorsid` )
    REFERENCES `authors` (`id` ),
  CONSTRAINT `fk_authorsthemes_themes`
    FOREIGN KEY (`themesid` )
    REFERENCES `themes` (`id` ) ) ;


-- -----------------------------------------------------
-- Table `bookspublishers`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bookspublishers` ;

CREATE  TABLE IF NOT EXISTS `bookspublishers` (
  `booksid` INTEGER NOT NULL ,
  `publishersid` INTEGER NOT NULL ,
  PRIMARY KEY (`booksid`, `publishersid`) ,
  CONSTRAINT `fk_bookspublishers_books`
    FOREIGN KEY (`booksid` )
    REFERENCES `books` (`id` ),
  CONSTRAINT `fk_bookspublishers_publishers`
    FOREIGN KEY (`publishersid` )
    REFERENCES `publishers` (`id` ) ) ;


-- -----------------------------------------------------
-- Table `authorspublishers`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `authorspublishers` ;

CREATE  TABLE IF NOT EXISTS `authorspublishers` (
  `authorsid` INTEGER NOT NULL ,
  `publishersid` INTEGER NOT NULL ,
  PRIMARY KEY (`authorsid`, `publishersid`) ,
  CONSTRAINT `fk_authorspublishers_authors`
    FOREIGN KEY (`authorsid` )
    REFERENCES `authors` (`id` ),
  CONSTRAINT `fk_authorspublishers_publishers`
    FOREIGN KEY (`publishersid` )
    REFERENCES `publishers` (`id` ) );


-- -----------------------------------------------------
-- Table `booksthemes`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `booksthemes` ;

CREATE  TABLE IF NOT EXISTS `booksthemes` (
  `booksid` INTEGER NOT NULL ,
  `themesid` INTEGER NOT NULL ,
  PRIMARY KEY (`booksid`, `themesid`) ,
  CONSTRAINT `fk_booksthemes_books`
    FOREIGN KEY (`booksid` )
    REFERENCES `books` (`id` ),
  CONSTRAINT `fk_booksthemes_themes`
    FOREIGN KEY (`themesid` )
    REFERENCES `themes` (`id` ) ) ;
