<?php

namespace Phalcon\Test\Integration\Mvc\Model;

use IntegrationTester;
use Phalcon\Test\Fixtures\Traits\DiTrait;
use Phalcon\Test\Models\Personnes;
use Phalcon\Test\Models\Pessoas;

class ModelsCalculationsCest
{
    use DiTrait;

    public function _before(IntegrationTester $I)
    {
        $this->setNewFactoryDefault();
    }

    public function testCalculationsMysql(IntegrationTester $I)
    {
        $this->setDiMysql();

        $this->executeTestsNormal($I);
        $this->executeTestsRenamed($I);
    }

    public function testCalculationsSqlite(IntegrationTester $I)
    {
        $this->setDiSqlite();

        $this->executeTestsNormal($I);
        $this->executeTestsRenamed($I);
    }

    /**
     * @medium
     */
    public function testCalculationsPostgresql(IntegrationTester $I)
    {
        $this->setDiPostgresql();

        $this->executeTestsNormal(
            $I,
            2196,
            2194,
            995386020.00,
            994819000.00,
            453272.32,
            453427.07
        );

        $this->executeTestsRenamed(
            $I,
            2196,
            2194,
            995386020.00,
            994819000.00,
            453272.32,
            453427.07
        );
    }

    protected function executeTestsNormal(
        IntegrationTester $I,
        $total_rows = 2180,
        $estado_rows = 2178,
        $cupo_sum = 995066020.00,
        $a_sum = 994499000.00,
        $cupo_average = 456452.30,
        $a_average = 456611.11
    ) {

        //Count calculations
        $rowcount = Personnes::count();
        $I->assertEquals($total_rows, $rowcount);

        $rowcount = Personnes::count(
            [
                'distinct' => 'estado',
            ]
        );
        $I->assertEquals(2, $rowcount);

        $rowcount = Personnes::count("estado='A'");
        $I->assertEquals($estado_rows, $rowcount);

        $group = Personnes::count(
            [
                'group' => 'estado',
            ]
        );
        $I->assertCount(2, $group);

        $group = Personnes::count(
            [
                'group' => 'estado',
                'order' => 'estado',
            ]
        );
        $I->assertCount(2, $group);

        $results = [
            'A' => $estado_rows,
            'I' => 2,
        ];

        foreach ($group as $row) {
            $I->assertEquals(
                $results[$row->estado],
                $row->rowcount
            );
        }

        $I->assertEquals(
            $estado_rows,
            $group[0]->rowcount
        );
        $I->assertEquals(
            2,
            $group[1]->rowcount
        );

        $group = Personnes::count(
            [
                'group' => 'estado',
            ]
        );
        $I->assertCount(2, $group);

        $group = Personnes::count(
            [
                'group' => 'ciudad_id',
            ]
        );
        $I->assertCount(285, $group);

        $group = Personnes::count(
            [
                'group' => 'ciudad_id',
                'order' => 'rowcount DESC',
            ]
        );
        $I->assertEquals($group[0]->rowcount, 727);

        //Summatory
        $total = Personnes::sum(
            [
                'column' => 'cupo',
            ]
        );
        $I->assertEquals($cupo_sum, $total);

        $total = Personnes::sum(
            [
                'column'     => 'cupo',
                'conditions' => "estado='I'",
            ]
        );
        $I->assertEquals(567020.00, $total);

        $group = Personnes::sum(
            [
                'column' => 'cupo', 'group' => 'estado',
            ]
        );
        $I->assertCount(2, $group);

        $results = ['A' => $a_sum, 'I' => 567020.00];
        foreach ($group as $row) {
            $I->assertEquals($results[$row->estado], $row->sumatory);
        }

        $group = Personnes::sum(
            [
                'column' => 'cupo',
                'group'  => 'ciudad_id',
                'order'  => 'sumatory DESC',
            ]
        );
        $I->assertEquals(358467690.00, $group[0]->sumatory);

        //Average
        $total = Personnes::average(
            [
                'column' => 'cupo',
            ]
        );
        $I->assertEquals($cupo_average, sprintf('%.2f', $total));

        $total = Personnes::average(
            [
                'column'     => 'cupo',
                'conditions' => "estado='I'",
            ]
        );
        $I->assertEquals(283510.00, $total);

        $group = Personnes::average(
            [
                'column' => 'cupo',
                'group'  => 'estado',
            ]
        );
        $I->assertCount(2, $group);

        $results = [
            'A' => $a_average,
            'I' => 283510.00,
        ];
        foreach ($group as $row) {
            $I->assertEquals(
                $results[$row->estado],
                sprintf('%.2f', $row->average)
            );
        }

        $group = Personnes::average(
            [
                'column' => 'cupo',
                'group'  => 'ciudad_id',
                'order'  => 'average DESC',
            ]
        );
        $I->assertEquals($group[0]->average, 996200.00);

        //Maximum
        $max = Personnes::maximum(
            [
                'column' => 'ciudad_id',
            ]
        );
        $I->assertEquals($max, 302172);

        $max = Personnes::maximum(
            [
                'column' => 'ciudad_id', 'conditions' => "estado='I'",
            ]
        );
        $I->assertEquals($max, 127591);

        $group = Personnes::maximum(
            [
                'column' => 'ciudad_id',
                'group'  => 'estado',
            ]
        );
        $I->assertCount(2, $group);

        $results = ['A' => 302172, 'I' => 127591];
        foreach ($group as $row) {
            $I->assertEquals($results[$row->estado], $row->maximum);
        }

        $group = Personnes::maximum(
            [
                'column' => 'ciudad_id',
                'group'  => 'estado',
                'order'  => 'maximum DESC',
            ]
        );
        $I->assertEquals($group[0]->maximum, 302172);

        //Minimum
        $max = Personnes::minimum(
            [
                'column' => 'ciudad_id',
            ]
        );
        $I->assertEquals($max, 20404);

        $max = Personnes::minimum(
            [
                'column'     => 'ciudad_id',
                'conditions' => "estado='I'",
            ]
        );
        $I->assertEquals($max, 127591);

        $group = Personnes::minimum(
            [
                'column' => 'ciudad_id',
                'group'  => 'estado',
            ]
        );
        $I->assertCount(2, $group);

        $results = ['A' => 20404, 'I' => 127591];
        foreach ($group as $row) {
            $I->assertEquals($results[$row->estado], $row->minimum);
        }

        $group = Personnes::minimum(
            [
                'column' => 'ciudad_id',
                'group' => 'estado',
                'order' => 'minimum DESC',
            ]
        );
        $I->assertEquals(
            127591,
            $group[0]->minimum
        );

        $group = Personnes::minimum(
            [
                'column' => 'ciudad_id',
                'group' => 'estado',
                'order' => 'minimum ASC',
            ]
        );
        $I->assertEquals(
            20404,
            $group[0]->minimum
        );
    }

    protected function executeTestsRenamed(
        IntegrationTester $I,
        $total_rows = 2180,
        $estado_rows = 2178,
        $cupo_sum = 995066020.00,
        $a_sum = 994499000.00,
        $cupo_average = 456452.30,
        $a_average = 456611.11
    ) {

        //Count calculations
        $rowcount = Pessoas::count();
        $I->assertEquals($total_rows, $rowcount);

        $rowcount = Pessoas::count(
            [
                'distinct' => 'estado',
            ]
        );
        $I->assertEquals(2, $rowcount);

        $rowcount = Pessoas::count("estado='A'");
        $I->assertEquals($estado_rows, $rowcount);

        $group = Pessoas::count(
            [
                'group' => 'estado',
            ]
        );

        $I->assertCount(2, $group);

        $group = Pessoas::count(
            [
                'group' => 'estado',
                'order' => 'estado',
            ]
        );
        $I->assertCount(2, $group);

        $results = [
            'A' => $estado_rows,
            'I' => 2,
        ];
        foreach ($group as $row) {
            $I->assertEquals(
                $results[$row->estado],
                $row->rowcount
            );
        }

        $I->assertEquals(
            $estado_rows,
            $group[0]->rowcount
        );
        $I->assertEquals(
            2,
            $group[1]->rowcount
        );

        $group = Pessoas::count(
            [
                'group' => 'estado',
            ]
        );

        $I->assertCount(2, $group);

        $group = Pessoas::count(
            [
                'group' => 'cidadeId',
            ]
        );

        $I->assertCount(285, $group);

        $group = Pessoas::count(
            [
                'group' => 'cidadeId',
                'order' => 'rowcount DESC',
            ]
        );
        $I->assertEquals(727, $group[0]->rowcount);

        //Summatory
        $total = Pessoas::sum(
            [
                'column' => 'credito',
            ]
        );

        $I->assertEquals($cupo_sum, $total);

        $total = Pessoas::sum(
            [
                'column'     => 'credito',
                'conditions' => "estado='I'",
            ]
        );
        $I->assertEquals(567020.00, $total);

        $group = Pessoas::sum(
            [
                'column' => 'credito',
                'group'  => 'estado',
            ]
        );
        $I->assertCount(2, $group);

        $results = [
            'A' => $a_sum,
            'I' => 567020.00,
        ];
        foreach ($group as $row) {
            $I->assertEquals(
                $results[$row->estado],
                $row->sumatory
            );
        }

        $group = Pessoas::sum(
            [
                'column' => 'credito',
                'group'  => 'cidadeId',
                'order'  => 'sumatory DESC',
            ]
        );
        $I->assertEquals(358467690.00, $group[0]->sumatory);

        //Average
        $total = Pessoas::average(
            [
                'column' => 'credito',
            ]
        );
        $I->assertEquals(
            $cupo_average,
            sprintf('%.2f', $total)
        );

        $total = Pessoas::average(
            [
                'column'     => 'credito',
                'conditions' => "estado='I'",
            ]
        );
        $I->assertEquals(283510.00, $total);

        $group = Pessoas::average(
            [
                'column' => 'credito',
                'group'  => 'estado',
            ]
        );
        $I->assertCount(2, $group);

        $results = [
            'A' => $a_average,
            'I' => 283510.00,
        ];
        foreach ($group as $row) {
            $I->assertEquals(
                $results[$row->estado],
                sprintf('%.2f', $row->average)
            );
        }

        $group = Pessoas::average(
            [
                'column' => 'credito',
                'group'  => 'cidadeId',
                'order'  => 'average DESC',
            ]
        );
        $I->assertEquals(996200.00, $group[0]->average);

        //Maximum
        $max = Pessoas::maximum(
            [
                'column' => 'cidadeId',
            ]
        );
        $I->assertEquals(302172, $max);

        $max = Pessoas::maximum(
            [
                'column'     => 'cidadeId',
                'conditions' => "estado='I'",
            ]
        );
        $I->assertEquals(127591, $max);

        $group = Pessoas::maximum(
            [
                'column' => 'cidadeId',
                'group'  => 'estado',
            ]
        );

        $I->assertCount(2, $group);

        $results = [
            'A' => 302172,
            'I' => 127591,
        ];

        foreach ($group as $row) {
            $I->assertEquals(
                $results[$row->estado],
                $row->maximum
            );
        }

        $group = Pessoas::maximum(
            [
                'column' => 'cidadeId',
                'group'  => 'estado',
                'order'  => 'maximum DESC',
            ]
        );

        $I->assertEquals(
            302172,
            $group[0]->maximum
        );

        //Minimum
        $max = Pessoas::minimum(
            [
                'column' => 'cidadeId',
            ]
        );

        $I->assertEquals(
            20404,
            $max
        );

        $max = Pessoas::minimum(
            [
                'column'     => 'cidadeId',
                'conditions' => "estado='I'",
            ]
        );

        $I->assertEquals(
            127591,
            $max
        );

        $group = Pessoas::minimum(
            [
                'column' => 'cidadeId',
                'group'  => 'estado',
            ]
        );
        $I->assertCount(2, $group);

        $results = [
            'A' => 20404,
            'I' => 127591,
        ];

        foreach ($group as $row) {
            $I->assertEquals(
                $results[$row->estado],
                $row->minimum
            );
        }

        $group = Pessoas::minimum(
            [
                'column' => 'cidadeId',
                'group'  => 'estado',
                'order'  => 'minimum DESC',
            ]
        );

        $I->assertEquals(
            127591,
            $group[0]->minimum
        );

        $group = Pessoas::minimum(
            [
                'column' => 'cidadeId',
                'group'  => 'estado',
                'order'  => 'minimum ASC',
            ]
        );

        $I->assertEquals(
            20404,
            $group[0]->minimum
        );
    }
}
