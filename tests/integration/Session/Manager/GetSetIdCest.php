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

namespace Phalcon\Test\Integration\Session\Manager;

use IntegrationTester;
use Phalcon\Session\Manager;
use Phalcon\Test\Fixtures\Traits\DiTrait;
use Phalcon\Test\Fixtures\Traits\SessionTrait;
use function uniqid;

class GetSetIdCest
{
    use DiTrait;
    use SessionTrait;

    /**
     * Tests Phalcon\Session\Manager :: getId()/setId()
     *
     * @author Phalcon Team <team@phalconphp.com>
     * @since  2018-11-13
     */
    public function sessionManagerGetSetId(IntegrationTester $I)
    {
        $I->wantToTest('Session\Manager - getId()/setId()');

        $manager = new Manager();

        $files = $this->getSessionStream();

        $manager->setHandler($files);

        $I->assertEquals(
            '',
            $manager->getId()
        );



        $id = uniqid();

        $manager->setId($id);

        $I->assertEquals(
            $id,
            $manager->getId()
        );

        $manager->destroy();
    }
}
