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

namespace Phalcon\Test\Unit\Crypt;

use UnitTester;

/**
 * Class UseSigningCest
 */
class UseSigningCest
{
    /**
     * Tests Phalcon\Crypt :: useSigning()
     *
     * @param UnitTester $I
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2019-04-16
     */
    public function cryptUseSigning(UnitTester $I)
    {
        $I->wantToTest('Crypt - useSigning()');

        $I->skipTest('Need implementation');
    }
}
