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

namespace Phalcon\Test\Integration\Validation;

use IntegrationTester;

/**
 * Class GetDICest
 */
class GetDICest
{
    /**
     * Tests Phalcon\Validation :: getDI()
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2019-04-16
     */
    public function validationGetDI(IntegrationTester $I)
    {
        $I->wantToTest('Validation - getDI()');

        $I->skipTest('Need implementation');
    }
}
