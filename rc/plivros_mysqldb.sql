SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL';


-- -----------------------------------------------------
-- Table `themes`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `themes` ;

CREATE  TABLE IF NOT EXISTS `themes` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `name` VARCHAR(20) NULL ,
  `description` TEXT NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `publishers`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `publishers` ;

CREATE  TABLE IF NOT EXISTS `publishers` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `name` VARCHAR(45) NULL ,
  `description` TEXT NULL ,
  `critique` TEXT NULL ,
  `logo` VARCHAR(256) NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `authors`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `authors` ;

CREATE  TABLE IF NOT EXISTS `authors` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `firstname` VARCHAR(45) NULL ,
  `lastname` VARCHAR(45) NULL ,
  `description` TEXT NULL ,
  `critique` TEXT NULL ,
  `rating` INT(3) NULL ,
  `picture` VARCHAR(256) NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `publishersthemes`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `publishersthemes` ;

CREATE  TABLE IF NOT EXISTS `publishersthemes` (
  `publishersid` INT NOT NULL ,
  `themesid` INT NOT NULL ,
  PRIMARY KEY (`publishersid`, `themesid`) ,
  INDEX `fk_publishersthemes_publishers` (`publishersid` ASC) ,
  INDEX `fk_publishersthemes_themes` (`themesid` ASC) ,
  CONSTRAINT `fk_publishersthemes_publishers`
    FOREIGN KEY (`publishersid` )
    REFERENCES `plivros`.`publishers` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_publishersthemes_themes`
    FOREIGN KEY (`themesid` )
    REFERENCES `plivros`.`themes` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);


-- -----------------------------------------------------
-- Table `books`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `books` ;

CREATE  TABLE IF NOT EXISTS `books` (
  `id` INT NOT NULL AUTO_INCREMENT ,
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
  PRIMARY KEY (`id`) ,
  INDEX `translator` (`id` ASC) ,
  CONSTRAINT `translator`
    FOREIGN KEY (`id` )
    REFERENCES `plivros`.`authors` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `booksauthors`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `booksauthors` ;

CREATE  TABLE IF NOT EXISTS `booksauthors` (
  `booksid` INT NOT NULL ,
  `authorsid` INT NOT NULL ,
  PRIMARY KEY (`booksid`, `authorsid`) ,
  INDEX `fk_booksauthors_books` (`booksid` ASC) ,
  INDEX `fk_booksauthors_authors` (`authorsid` ASC) ,
  CONSTRAINT `fk_booksauthors_books`
    FOREIGN KEY (`booksid` )
    REFERENCES `plivros`.`books` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_booksauthors_authors`
    FOREIGN KEY (`authorsid` )
    REFERENCES `plivros`.`authors` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);


-- -----------------------------------------------------
-- Table `authorsthemes`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `authorsthemes` ;

CREATE  TABLE IF NOT EXISTS `authorsthemes` (
  `authorsid` INT NOT NULL ,
  `themesid` INT NOT NULL ,
  PRIMARY KEY (`authorsid`, `themesid`) ,
  INDEX `fk_authorsthemes_authors` (`authorsid` ASC) ,
  INDEX `fk_authorsthemes_themes` (`themesid` ASC) ,
  CONSTRAINT `fk_authorsthemes_authors`
    FOREIGN KEY (`authorsid` )
    REFERENCES `plivros`.`authors` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_authorsthemes_themes`
    FOREIGN KEY (`themesid` )
    REFERENCES `plivros`.`themes` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);


-- -----------------------------------------------------
-- Table `bookspublishers`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bookspublishers` ;

CREATE  TABLE IF NOT EXISTS `bookspublishers` (
  `booksid` INT NOT NULL ,
  `publishersid` INT NOT NULL ,
  PRIMARY KEY (`booksid`, `publishersid`) ,
  INDEX `fk_bookspublishers_books` (`booksid` ASC) ,
  INDEX `fk_bookspublishers_publishers` (`publishersid` ASC) ,
  CONSTRAINT `fk_bookspublishers_books`
    FOREIGN KEY (`booksid` )
    REFERENCES `plivros`.`books` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_bookspublishers_publishers`
    FOREIGN KEY (`publishersid` )
    REFERENCES `plivros`.`publishers` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);


-- -----------------------------------------------------
-- Table `authorspublishers`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `authorspublishers` ;

CREATE  TABLE IF NOT EXISTS `authorspublishers` (
  `authorsid` INT NOT NULL ,
  `publishersid` INT NOT NULL ,
  PRIMARY KEY (`authorsid`, `publishersid`) ,
  INDEX `fk_authorspublishers_authors` (`authorsid` ASC) ,
  INDEX `fk_authorspublishers_publishers` (`publishersid` ASC) ,
  CONSTRAINT `fk_authorspublishers_authors`
    FOREIGN KEY (`authorsid` )
    REFERENCES `plivros`.`authors` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_authorspublishers_publishers`
    FOREIGN KEY (`publishersid` )
    REFERENCES `plivros`.`publishers` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);


-- -----------------------------------------------------
-- Table `booksthemes`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `booksthemes` ;

CREATE  TABLE IF NOT EXISTS `booksthemes` (
  `booksid` INT NOT NULL ,
  `themesid` INT NOT NULL ,
  PRIMARY KEY (`booksid`, `themesid`) ,
  INDEX `fk_booksthemes_books` (`booksid` ASC) ,
  INDEX `fk_booksthemes_themes` (`themesid` ASC) ,
  CONSTRAINT `fk_booksthemes_books`
    FOREIGN KEY (`booksid` )
    REFERENCES `plivros`.`books` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_booksthemes_themes`
    FOREIGN KEY (`themesid` )
    REFERENCES `plivros`.`themes` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION);



SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
