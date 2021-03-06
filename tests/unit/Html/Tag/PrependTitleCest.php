<?php
declare(strict_types=1);

/**
 * This file is part of the Phalcon Framework.
 *
 * (c) Phalcon Team <team@phalconphp.com>
 *
 * For the full copyright and license information, please view the LICENSE.txt
 * file that was distributed with this source code.
 */

namespace Phalcon\Test\Unit\Html\Tag;

use Phalcon\Html\Tag;
use Phalcon\Test\Fixtures\Traits\DiTrait;
use Phalcon\Test\Fixtures\Traits\TagSetupTrait;
use const PHP_EOL;
use UnitTester;

class PrependTitleCest
{
    use DiTrait;
    use TagSetupTrait;

    /**
     * Tests Phalcon\Html\Tag :: prependTitle()
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2018-11-13
     */
    public function htmlTagPrependTitle(UnitTester $I)
    {
        $I->wantToTest('Html\Tag - prependTitle()');

        $tag = new Tag();
        $tag->setDI($this->container);
        $tag
            ->setTitle('Title')
            ->prependTitle(['Class'])
        ;

        $expected = 'Title';
        $actual   = $tag->getTitle(false);
        $I->assertEquals($expected, $actual);

        $expected = 'ClassTitle';
        $actual   = $tag->getTitle(true);
        $I->assertEquals($expected, $actual);

        $expected = '<title>ClassTitle</title>' . PHP_EOL;
        $actual   = $tag->renderTitle();
        $I->assertEquals($expected, $actual);
    }

    /**
     * Tests Phalcon\Html\Tag :: prependTitle() - string
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2018-11-13
     */
    public function htmlTagAppendTitleString(UnitTester $I)
    {
        $I->wantToTest('Html\Tag - prependTitle() - string');

        $tag = new Tag();
        $tag->setDI($this->container);

        $tag
            ->setTitle('Title')
            ->prependTitle('Class')
        ;

        $I->assertEquals(
            'Title',
            $tag->getTitle(false, false)
        );

        $I->assertEquals(
            'ClassTitle',
            $tag->getTitle(true, false)
        );

        $I->assertEquals(
            '<title>ClassTitle</title>' . PHP_EOL,
            $tag->renderTitle()
        );
    }

    /**
     * Tests Phalcon\Html\Tag :: prependTitle() - separator
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2018-11-13
     */
    public function htmlTagPrependTitleSeparator(UnitTester $I)
    {
        $I->wantToTest('Html\Tag - prependTitle() - separator');

        $tag = new Tag();
        $tag->setDI($this->container);

        $tag
            ->setTitle('Title')
            ->setTitleSeparator('|')
            ->prependTitle(['Class'])
        ;

        $expected = 'Title';
        $actual   = $tag->getTitle(false);
        $I->assertEquals($expected, $actual);

        $expected = 'Class|Title';
        $actual   = $tag->getTitle(true);
        $I->assertEquals($expected, $actual);

        $expected = '<title>Class|Title</title>' . PHP_EOL;
        $actual   = $tag->renderTitle();
        $I->assertEquals($expected, $actual);
    }

    /**
     * Tests Phalcon\Html\Tag :: prependTitle() - double call
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2018-11-13
     */
    public function htmlTagPrependTitleDoubleCall(UnitTester $I)
    {
        $I->wantToTest('Html\Tag - prependTitle() - double call');
        $tag = new Tag();
        $tag->setDI($this->container);

        $tag
            ->setTitle('Main')
            ->setTitleSeparator(' - ')
            ->prependTitle('Category')
            ->prependTitle('Title')
        ;

        $expected = 'Main';
        $actual   = $tag->getTitle(false);
        $I->assertEquals($expected, $actual);

        $expected = 'Title - Category - Main';
        $actual   = $tag->getTitle(true);
        $I->assertEquals($expected, $actual);

        $expected = '<title>Title - Category - Main</title>' . PHP_EOL;
        $actual   = $tag->renderTitle();
        $I->assertEquals($expected, $actual);
    }

    /**
     * Tests Phalcon\Html\Tag :: prependTitle() - many
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2018-11-13
     */
    public function htmlTagPrependTitleMany(UnitTester $I)
    {
        $I->wantToTest('Html\Tag - prependTitle() - many');
        $tag = new Tag();
        $tag->setDI($this->container);

        $tag
            ->setTitle('Main')
            ->setTitleSeparator(' - ')
            ->prependTitle(['Category', 'Title'])
        ;

        $expected = 'Main';
        $actual   = $tag->getTitle(false);
        $I->assertEquals($expected, $actual);

        $expected = 'Title - Category - Main';
        $actual   = $tag->getTitle(true);
        $I->assertEquals($expected, $actual);

        $expected = '<title>Title - Category - Main</title>' . PHP_EOL;
        $actual   = $tag->renderTitle();
        $I->assertEquals($expected, $actual);
    }

    /**
     * Tests Phalcon\Html\Tag :: prependTitle() - empty array
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2018-11-13
     */
    public function htmlTagPrependTitleEmptyArray(UnitTester $I)
    {
        $I->wantToTest('Html\Tag - prependTitle() - empty array');
        $tag = new Tag();
        $tag->setDI($this->container);

        $tag
            ->setTitle('Main')
            ->setTitleSeparator(' - ')
            ->prependTitle([])
        ;

        $expected = 'Main';
        $actual   = $tag->getTitle(false);
        $I->assertEquals($expected, $actual);

        $expected = 'Main';
        $actual   = $tag->getTitle(true);
        $I->assertEquals($expected, $actual);

        $expected = '<title>Main</title>' . PHP_EOL;
        $actual   = $tag->renderTitle();
        $I->assertEquals($expected, $actual);
    }
}
